#ifndef WEEKLYSCHEDULEDELETE_H
#define WEEKLYSCHEDULEDELETE_H

#include "tool.h"
#include "timethread.h"

namespace Ui {
class WeeklyScheduleDelete;
}

class WeeklyScheduleDelete : public QDialog
{
    Q_OBJECT

public:
    explicit WeeklyScheduleDelete(QWidget *parent = nullptr);
    ~WeeklyScheduleDelete();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetThread();

private slots:
    void on_Selectday_currentIndexChanged(const QString &arg1);
    void on_Delete_btn_clicked();
    void UpdateWeekly(QString);
    void UpdateToday(QString);
    void TodayEnd();

private:
    Ui::WeeklyScheduleDelete *ui;
    QString dow;
    SOCKET sock;
    string id;
    TimeThread* thr;
};

#endif // WEEKLYSCHEDULEDELETE_H
