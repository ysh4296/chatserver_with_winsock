#include "timetable.h"
#include "ui_timetable.h"

Timetable::Timetable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Timetable)
{
    ui->setupUi(this);
    week = new WeeklyScheduleAdd(this);
    weekdel = new WeeklyScheduleDelete(this);
    day = new DailyScheduleAdd(this);
    ui->CurrentTime->setDateTime(QDateTime::currentDateTime());

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    thr = new TimeThread(this);
    QObject::connect(thr, SIGNAL(DailySchedulSend(QString)), this, SLOT(UpdateToday(QString)));                 //001
    QObject::connect(thr, SIGNAL(TodayEnd()), this, SLOT(TodayEnd()));                                          //000
    QObject::connect(thr, SIGNAL(WeeklySchedulSend(QString)), this, SLOT(UpdateWeekly(QString)));               //003
    QObject::connect(thr, SIGNAL(GroupSchedulSend(QString)), this, SLOT(UpdateGroup(QString)));                 //011
}

Timetable::~Timetable()
{
    delete week;
    delete day;
    delete ui;
    thr->terminate();
    thr->quit();
    delete thr;
}

void Timetable::updateTime()
{
    ui->CurrentTime->setDateTime( QDateTime::currentDateTime() );
}

void Timetable::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Timetable::GetSocket() {
    return sock;
}

void Timetable::SetId(string i) {
    id = i;
}

string Timetable::GetId() {
    return id;
}

void Timetable::Send000() {
    QString str;
    if (ui->calendarWidget->selectedDate().isNull()) {
        Date = ui->CurrentTime->date();
        str = QLocale{QLocale::English}.toString(Date, "yy,MM,dd ddd").toLower();
    }
    else {
        Date = ui->calendarWidget->selectedDate();
         str = QLocale{QLocale::English}.toString(Date, "yy,MM,dd ddd").toLower();
    }
    string da = str.toUtf8().constData();
    string msg = "000 " + da;
    qDebug(msg.c_str());

    ui->GroupSchedule_list->clear();
    ui->WeeklySchedule_list->clear();
    ui->DailySchedule_list->clear();
    Sleep(10);
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void Timetable::SendtTI() {
    string msg = "TimeTable";
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    Sleep(10);
    send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
}

void Timetable::Thre() {
    thr->SetId(id);
    thr->SetSocket(sock);
    thr->start();
}

void Timetable::on_calendarWidget_clicked(const QDate &date)
{
//    Date = ui->calendarWidget->selectedDate();
//    QString str = QLocale{QLocale::English}.toString(date, "yy.MM.dd ddd").toLower();
//    string da = str.toUtf8().constData();
//    qDebug(da.c_str());
////005 yy/mm/dd ss,se,es,ee dow eff    주간일정추가
////004 ss,se,es,ee dow        주간일정삭제
////002 yy/mm/dd ss,se,es,ee dow eff    일간일정추가 004 성공 다시 000 005 실패
////003 yy/mm/dd ss,se,es,ee dow        일간일정삭제
////000 yy/mm/dd dow
////001 일간일정 000
////003 주간일정 002
//    thr->terminate();

//    Schedule sche;
//    da = da + " Schedule";
//    sche.setWindowTitle(da.c_str());
//    sche.SetSocket(sock);
//    sche.SetId(id);
//    sche.SetDate(str);
//    sche.SetThread();
//    sche.SetList();
//    sche.exec();

//    thr->start();

    Send000();
}

void Timetable::on_Messanger_btn_clicked()
{

    thr->terminate();

    List list;
    list.setWindowTitle("Friend&Chatting room List");
    list.SetSocket(GetSocket());
    list.SetId(GetId());
    string msg = "001";
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    list.Receive();
    list.Thre();
    list.exec();

    thr->start();

    Sleep(10);
    Send000();
}

void Timetable::on_WeekSCheduleAdd_btn_clicked()
{
    QString Dat = ui->CurrentTime->date().toString("yy,MM,dd");
    week->SetToday(Dat);
    week->SetSocket(sock);
    week->SetId(id);
    week->SetThread(thr);
    week->setModal(true);
    week->exec();

    Sleep(10);
    Send000();
}
//004 ss,se,es,ee dow        주간일정삭제
void Timetable::on_WeekSCheduleDelete_btn_clicked() {

    thr->terminate();

    weekdel->SetSocket(sock);
    weekdel->SetId(id);
    weekdel->SetThread();
    weekdel->setModal(true);
    weekdel->exec();

    thr->start();

    Sleep(10);
    Send000();
}

void Timetable::UpdateToday(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(2, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->DailySchedule_list->addItem(sche);
}

void Timetable::TodayEnd() {
    Sleep(10);
}

void Timetable::UpdateWeekly(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(2, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->WeeklySchedule_list->addItem(sche);
}

void Timetable::UpdateGroup(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(2, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QStringList lst = Do.split("|");

    QString sche = Time + " " + lst[2] + "|" + lst[1];
    ui->GroupSchedule_list->addItem(sche);
}

void Timetable::on_DaySCheduleAdd_btn_clicked()
{
    Date = ui->calendarWidget->selectedDate();
    QString str = QLocale{QLocale::English}.toString(Date, "yy,MM,dd ddd").toLower();
    QString dow = str;
    QString Dat = str;
    day->SetDayofWeek(dow.remove(0, 9));
    Dat.truncate(Dat.lastIndexOf(" "));
    day->SetDate(Dat);
    day->SetSocket(sock);
    day->SetId(id);
    day->SetThread(thr);
    day->setModal(true);
    day->exec();

    Sleep(10);
    Send000();
}
//003 yy/mm/dd ss,se,es,ee dow        일간일정삭제
void Timetable::on_DaySCheduleDelete_btn_clicked()
{
    Date = ui->calendarWidget->selectedDate();
    QString str = QLocale{QLocale::English}.toString(Date, "yy,MM,dd ddd").toLower();
    QString dow = str;
    QString Dat = str;
    QMessageBox Msgbox;
    dow.remove(0, 9);
    Dat.truncate(Dat.lastIndexOf(" "));

    QString sel = ui->DailySchedule_list->currentItem()->text();
    QString ss = sel;
    ss.remove(0, ss.lastIndexOf(" "));
    if (strcmp(ss.toUtf8().constData(), " Schedule") == 0) {
        Msgbox.setText("This is not Schedule");
        Msgbox.exec();
    }
    else {
    QStringList ls = sel.split(" ~ ");
    QStringList sls = ls[0].split(":");
    QStringList els = ls[1].split(":");
    QString sh = sls[0];
    QString sm = sls[1];
    QString eh = els[0];
    QString em = els[1];
    em.remove(2,em.size());

    QString qst =  Dat.append(" ").append(sh).append(",").append(sm).append(",").append(eh).append(",").append(em).append(" ").append(dow);
    string da = qst.toUtf8().constData();
    string msg = "003 " + da;
    qDebug(msg.c_str());
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    Msgbox.setText("Schedule remove");
    Msgbox.exec();

    Sleep(10);
    Send000();
    }
}
