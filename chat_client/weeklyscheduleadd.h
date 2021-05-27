#ifndef WEEKLYSCHEDULEADD_H
#define WEEKLYSCHEDULEADD_H

#include "tool.h"
#include "timethread.h"

namespace Ui {
class WeeklyScheduleAdd;
}

class WeeklyScheduleAdd : public QDialog
{
    Q_OBJECT

public:
    explicit WeeklyScheduleAdd(QWidget *parent = nullptr);
    ~WeeklyScheduleAdd();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetToday(QString s);
    void SetThread(TimeThread* t);

private slots:
    void on_Add_btn_clicked();
    void Success();
    void FailedbyDaily(QString);
    void FailedbyWeek();
    void FailedbyGroup(QString);

private:
    Ui::WeeklyScheduleAdd *ui;
    QString Date;
    QString DOW;
    QString StartTime;
    QString EndTime;
    QString Contents;
    SOCKET sock;
    string id;
    TimeThread* thr;
};

#endif // WEEKLYSCHEDULEADD_H
