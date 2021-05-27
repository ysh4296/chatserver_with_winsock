#ifndef DAILYSCHEDULEADD_H
#define DAILYSCHEDULEADD_H

#include "tool.h"
#include "timethread.h"

namespace Ui {
class DailyScheduleAdd;
}

class DailyScheduleAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DailyScheduleAdd(QWidget *parent = nullptr);
    ~DailyScheduleAdd();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetDate(QString d);
    void SetDayofWeek(QString dow);
    void SetThread(TimeThread* t);

private slots:
    void on_Add_btn_clicked();
    void Success();
    void Failed();

private:
    Ui::DailyScheduleAdd *ui;
    QString Date;
    QString DOW;
    QString StartTime;
    QString EndTime;
    QString Contents;
    SOCKET sock;
    string id;
    TimeThread* thr;
};

#endif // DAILYSCHEDULEADD_H
