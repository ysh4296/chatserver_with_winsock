#ifndef TIMETABLE_H
#define TIMETABLE_H

#include "tool.h"
#include "receiver.h"
#include "list.h"
#include "schedule.h"
#include "weeklyscheduleadd.h"
#include "weeklyscheduledelete.h"
#include "dailyscheduleadd.h"
#include "timethread.h"

namespace Ui {
class Timetable;
}

class Timetable : public QDialog
{
    Q_OBJECT

public:
    explicit Timetable(QWidget *parent = nullptr);
    ~Timetable();    
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void Send000();
    void Thre();
    void SendtTI();

private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_Messanger_btn_clicked();
    void on_WeekSCheduleAdd_btn_clicked();
    void on_WeekSCheduleDelete_btn_clicked();
    void updateTime();
    void UpdateToday(QString);
    void UpdateWeekly(QString);
    void UpdateGroup(QString);
    void TodayEnd();
    void on_DaySCheduleAdd_btn_clicked();
    void on_DaySCheduleDelete_btn_clicked();

private:
    Ui::Timetable *ui;
    SOCKET sock;
    string id;
    WeeklyScheduleAdd* week;
    WeeklyScheduleDelete* weekdel;
    DailyScheduleAdd* day;
    QDate Date;
    TimeThread* thr;
};

#endif // TIMETABLE_H
