#include "schedule.h"
#include "ui_schedule.h"

Schedule::Schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Schedule)
{
    ui->setupUi(this);
    thr = new TimeThread(this);
    day = new DailyScheduleAdd(this);


    QObject::connect(thr, SIGNAL(DailySchedulSend(QString)), this, SLOT(UpdateToday(QString)));
    QObject::connect(thr, SIGNAL(TodayEnd()), this, SLOT(TodayEnd()));
    QObject::connect(thr, SIGNAL(WeeklySchedulSend(QString)), this, SLOT(UpdateWeekly(QString)));
}

Schedule::~Schedule()
{
    delete day;
    thr->terminate();
    thr->quit();
    delete thr;
    delete ui;
}

void Schedule::SetSocket(SOCKET s) {
    sock = s;
}

void Schedule::SetId(string i) {
    id = i;
}

void Schedule::SetDate(QString d) {
    date = d;

    QString day = d;
    QString week = d;
    day.append(" Daily Schedule");
    week.append(" Weekly Schedule");
    ui->Today->setText(day);
    ui->label->setText(week);
}

void Schedule::SetThread() {
   thr->SetId(id);
   thr->SetSocket(sock);
   thr->start();
}

void Schedule::on_DaySCheduleAdd_btn_clicked() {
    QString dow = date;
    QString Dat = date;
    day->SetDayofWeek(dow.remove(0, 9));
    Dat.truncate(Dat.lastIndexOf(" "));
    day->SetDate(Dat);
    day->SetSocket(sock);
    day->SetId(id);
    day->SetThread(thr);
    day->setModal(true);
    day->exec();

    Sleep(10);
    SetList();
}

void Schedule::on_DaySCheduleDelete_btn_clicked() {
    QString dow = date;
    QString Dat = date;
    dow.remove(0, 9);
    Dat.truncate(Dat.lastIndexOf(" "));

    QString sel = ui->DailySchedule_list->currentItem()->text();
    QString ss = sel;
    ss = ss.remove(0, ss.lastIndexOf(" "));
    if (strcmp(ss.toUtf8().constData(), " Schedule") == 0) {
        QMessageBox Msgbox;
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

    Sleep(10);
    SetList();
    }
}
//003 yy/mm/dd ss,se,es,ee dow        일간일정삭제
void Schedule::SetList() {
    string da = date.toUtf8().constData();
    string msg = "000 " + da;
    qDebug(msg.c_str());

    ui->WeeklySchedule_list->clear();
    ui->DailySchedule_list->clear();

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void Schedule::UpdateToday(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(3, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->DailySchedule_list->addItem(sche);
}

void Schedule::UpdateWeekly(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(3, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->WeeklySchedule_list->addItem(sche);
}

void Schedule::TodayEnd() {
    Sleep(10);
}

