#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "tool.h"
#include "dailyscheduleadd.h"
#include "timethread.h"

namespace Ui {
class Schedule;
}

class Schedule : public QDialog
{
    Q_OBJECT

public:
    explicit Schedule(QWidget *parent = nullptr);
    ~Schedule();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetDate(QString d);
    void SetThread();
    void SetList();

private slots:
    void on_DaySCheduleAdd_btn_clicked();
    void on_DaySCheduleDelete_btn_clicked();
    void UpdateToday(QString);
    void UpdateWeekly(QString);
    void TodayEnd();

private:
    Ui::Schedule *ui;
    SOCKET sock;
    string id;
    QString date;
    DailyScheduleAdd* day;
    TimeThread* thr;
};

#endif // SCHEDULE_H
