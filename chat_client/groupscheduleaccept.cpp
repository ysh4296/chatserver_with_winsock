#include "groupscheduleaccept.h"
#include "ui_groupscheduleaccept.h"

GroupScheduleAccept::GroupScheduleAccept(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupScheduleAccept)
{
    ui->setupUi(this);

    QObject::connect(thr, SIGNAL(GroupAddSuccess()), this, SLOT(Success()));      //003 성공
    QObject::connect(thr, SIGNAL(GroupAddFailed()), this, SLOT(Failed()));        //004 실패
    QObject::connect(thr, SIGNAL(GroupMember(QString)), this, SLOT(Failed(ResetList(QString))));        //010 참여자확인
}

GroupScheduleAccept::~GroupScheduleAccept()
{
    delete ui;
}

void GroupScheduleAccept::SetSocket(SOCKET s) {
    sock = s;
}

void GroupScheduleAccept::SetId(string i) {
    id = i;
}

void GroupScheduleAccept::SetThread() {
    thr->SetId(id);
    thr->SetSocket(sock);
    thr->start();
}

void GroupScheduleAccept::SetRoomName(string s) {
    R_Name = s;
}

void GroupScheduleAccept::SetDate(QString s) {
    Date = s;
}

void GroupScheduleAccept::SetTime(QString s) {
    Time = s;
}

void GroupScheduleAccept::SetDOW(QString s) {
    DOW = s;
}

void GroupScheduleAccept::SetContents(QString s) {
    Contents = s;
}

void GroupScheduleAccept::on_Accept_clicked() {

    QString ss = "008 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(Date).append(" ").append(Time).append(" ").append(DOW).append(" ").append(Contents);

    string msg = ss.toUtf8().constData();
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    SetList();
}

void GroupScheduleAccept::on_Reject_clicked() {
    QString ss = "009 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(Date).append(" ").append(Time).append(" ").append(DOW).append(" ").append(Contents);

    string msg = ss.toUtf8().constData();
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Didn't participate in the schedule"));
    Msgbox.exec();

    SetList();
}

void GroupScheduleAccept::Success() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Schedule added"));
    Msgbox.exec();
    this->close();
}

void GroupScheduleAccept::Failed() {
    QMessageBox Msgbox;
    Msgbox.setText(QString::fromLocal8Bit("Overlaps with another schedule"));
    Msgbox.exec();
    this->close();
}

void GroupScheduleAccept::SetList() {
    QString ss = "011 ";
    qDebug(Contents.toUtf8().constData());
    ss = ss.append(R_Name.c_str()).append(" ").append(Date).append(" ").append(Time).append(" ").append(DOW).append(" ").append(Contents);

    string msg = ss.toUtf8().constData();
    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void GroupScheduleAccept::ResetList(QString str) {
    QStringList lst = str.split(",");
    ui->GroupList->clear();
    for(int i = 0; i < lst.size(); i++) {
        ui->GroupList->addItem(lst[i]);
    }
}
