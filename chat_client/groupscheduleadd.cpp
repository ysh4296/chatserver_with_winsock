#include "groupscheduleadd.h"
#include "ui_groupscheduleadd.h"

GroupScheduleAdd::GroupScheduleAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupScheduleAdd)
{
    ui->setupUi(this);
    ui->GroupDate->setDate(QDate::currentDate());
}

GroupScheduleAdd::~GroupScheduleAdd()
{
    delete ui;
}


void GroupScheduleAdd::SetSocket(SOCKET s) {
    sock = s;
}

void GroupScheduleAdd::SetId(string i) {
    id = i;
}

void GroupScheduleAdd::SetRoomName(string s) {
    R_Name = s;
}

void GroupScheduleAdd::SetFilePath(QString q) {
    filepath = q;
}

void GroupScheduleAdd::SetThread(QThread *t) {
    thr = t;
}

void GroupScheduleAdd::on_Add_btn_clicked()
{
    QObject::disconnect(thr, SIGNAL(GroupAddSuccess()), this, SLOT(Success()));      //003 성공
    QObject::disconnect(thr, SIGNAL(GroupAddFailed()), this, SLOT(Failed()));        //004 실패
    QDate Date = ui->GroupDate->date();
    QString str = QLocale{QLocale::English}.toString(Date, "yy,MM,dd ddd").toLower();
    QString day = str.split(" ").at(0);
    QString StartTime = ui->GroupStartTime->time().toString("hh,mm");
    QString EndTime = ui->GroupEndTime->time().toString("hh,mm");
    QString Dow = str.split(" ").at(1);
    QString Contents = ui->GroupContents->text().toUtf8();

    QString ss = "007 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(day).append(" ").append(StartTime).append(",").append(EndTime).append(" ").append(Dow);

    string contents = Contents.toLocal8Bit().constData();


    string sibal = ss.toLocal8Bit().constData();
    string msg = sibal + " " + contents;
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    QObject::connect(thr, SIGNAL(GroupAddSuccess()), this, SLOT(Success()));      //003 성공
    QObject::connect(thr, SIGNAL(GroupAddFailed()), this, SLOT(Failed()));        //004 실패
}

void GroupScheduleAdd::Success() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Schedule added"));
    Msgbox.exec();
    this->close();
}

void GroupScheduleAdd::Failed() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlaps with another schedule"));
    Msgbox.exec();
    this->close();
}
