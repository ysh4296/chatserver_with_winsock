#include "weeklyscheduleadd.h"
#include "ui_weeklyscheduleadd.h"

WeeklyScheduleAdd::WeeklyScheduleAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeeklyScheduleAdd)
{
    ui->setupUi(this);
    ui->WeekSelect->addItem("mon");
    ui->WeekSelect->addItem("tue");
    ui->WeekSelect->addItem("wed");
    ui->WeekSelect->addItem("thu");
    ui->WeekSelect->addItem("fri");
    ui->WeekSelect->addItem("sat");
    ui->WeekSelect->addItem("sun");
}

WeeklyScheduleAdd::~WeeklyScheduleAdd()
{
    delete ui;
}

void WeeklyScheduleAdd::SetSocket(SOCKET s) {
    sock = s;
}

void WeeklyScheduleAdd::SetId(string i) {
    id = i;
}

void WeeklyScheduleAdd::SetToday(QString s) {
    Date = s;
}

void WeeklyScheduleAdd::SetThread(TimeThread* t) {
    thr = t;
}

void WeeklyScheduleAdd::on_Add_btn_clicked()
{
    QObject::disconnect(thr, SIGNAL(WeeklyAddSuccess()), this, SLOT(Success()));                            //006 성공
    QObject::disconnect(thr, SIGNAL(WeeklyAddFailedbyDaily(QString)), this, SLOT(FailedbyDaily(QString)));  //008 일간과겹침
    QObject::disconnect(thr, SIGNAL(WeeklyAddFailedbyWeek()), this, SLOT(FailedbyWeek()));                  //009 주간과겹침
    QObject::disconnect(thr, SIGNAL(WeeklyAddFailedbyGroup(QString)), this, SLOT(FailedbyGroup(QString)));  //010 그룹과겹침

    DOW = ui->WeekSelect->currentText();
    StartTime = ui->WeekStartTime->time().toString("hh,mm");
    EndTime = ui->WeekEndTime->time().toString("hh,mm");
    Contents = ui->WeekContents->text();

    QString str = "005 ";
    str = str.append(Date);
    str = str.append(" ");
    str = str.append(StartTime);
    str = str.append(",");
    str = str.append(EndTime);
    str = str.append(" ");
    str = str.append(DOW);
    str = str.append(" ");
    str = str.append(Contents);

    qDebug(str.toUtf8().constData());

    string msg = str.toUtf8().constData();

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    QObject::connect(thr, SIGNAL(WeeklyAddSuccess()), this, SLOT(Success()));                            //006 성공
    QObject::connect(thr, SIGNAL(WeeklyAddFailedbyDaily(QString)), this, SLOT(FailedbyDaily(QString)));  //008 일간과겹침
    QObject::connect(thr, SIGNAL(WeeklyAddFailedbyWeek()), this, SLOT(FailedbyWeek()));                  //009 주간과겹침
    QObject::connect(thr, SIGNAL(WeeklyAddFailedbyGroup(QString)), this, SLOT(FailedbyGroup(QString)));  //010 그룹과겹침

}
//005 yy/mm/dd ss,se,es,ee dow eff    주간일정추가

void WeeklyScheduleAdd::Success() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Schedule added"));
    Msgbox.exec();
    this->close();
}

void WeeklyScheduleAdd::FailedbyDaily(QString str) {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlap with the another daily schdule"));
    Msgbox.exec();
    this->close();
}

void WeeklyScheduleAdd::FailedbyWeek() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlap with the another weekly schdule"));
    Msgbox.exec();
    this->close();
}

void WeeklyScheduleAdd::FailedbyGroup(QString str) {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlap with the another group schdule"));
    Msgbox.exec();
    this->close();
}
