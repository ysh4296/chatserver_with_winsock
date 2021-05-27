#include "weeklyscheduledelete.h"
#include "ui_weeklyscheduledelete.h"

WeeklyScheduleDelete::WeeklyScheduleDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeeklyScheduleDelete)
{
    ui->setupUi(this);
    thr = new TimeThread(this);

    QObject::connect(thr, SIGNAL(DailySchedulSend(QString)), this, SLOT(UpdateToday(QString)));
    QObject::connect(thr, SIGNAL(TodayEnd()), this, SLOT(TodayEnd()));
    QObject::connect(thr, SIGNAL(WeeklySchedulSend(QString)), this, SLOT(UpdateWeekly(QString)));
}

WeeklyScheduleDelete::~WeeklyScheduleDelete()
{
    delete ui;
}

void WeeklyScheduleDelete::SetSocket(SOCKET s) {
    sock = s;
}

void WeeklyScheduleDelete::SetId(string i) {
    id = i;
}

void WeeklyScheduleDelete::SetThread() {
   thr->SetId(id);
   thr->SetSocket(sock);
   thr->start();
}

void WeeklyScheduleDelete::on_Selectday_currentIndexChanged(const QString &arg1)
{
    dow = arg1;
    string str = dow.toUtf8().constData();
    string msg = "000 00.00.00 " + str;

    ui->WeekScheduleList->clear();

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
}

void WeeklyScheduleDelete::on_Delete_btn_clicked()
{
    QMessageBox Msgbox;

    QString sel = ui->WeekScheduleList->currentItem()->text();
    QStringList ls = sel.split(" ~ ");
    QStringList sls = ls[0].split(":");
    QStringList els = ls[1].split(":");
    QString sh = sls[0];
    QString sm = sls[1];
    QString eh = els[0];
    QString em = els[1];
    em.remove(2,em.size());

    QString qst =  sh.append(",").append(sm).append(",").append(eh).append(",").append(em).append(" ").append(dow);

    string str = qst.toUtf8().constData();
    string msg = "004 " + str;

    qDebug(msg.c_str());

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    Msgbox.setText("Schedule remove");
    Msgbox.exec();

    this->close();
}

void WeeklyScheduleDelete::UpdateWeekly(QString str) {
    QString Do = str;
    QStringList ls = str.split(",");
    ls[3].remove(2, ls[3].size());
    Do.remove(0, 12);
    QString Time = ls[0].append(":").append(ls[1]).append(" ~ ").append(ls[2]).append(":").append(ls[3]);

    QString sche = Time + " " + Do;
    ui->WeekScheduleList->addItem(sche);
}

void WeeklyScheduleDelete::UpdateToday(QString) {

}

void WeeklyScheduleDelete::TodayEnd() {

}
