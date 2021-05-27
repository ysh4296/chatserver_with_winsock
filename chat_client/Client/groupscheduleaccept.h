#ifndef GROUPSCHEDULEACCEPT_H
#define GROUPSCHEDULEACCEPT_H

#include "tool.h"
#include "thread.h"

namespace Ui {
class GroupScheduleAccept;
}

class GroupScheduleAccept : public QDialog
{
    Q_OBJECT

public:
    explicit GroupScheduleAccept(QWidget *parent = nullptr);
    ~GroupScheduleAccept();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetRoomName(string s);
    void SetThread();
    void SetDate(QString s);
    void SetTime(QString s);
    void SetDOW(QString s);
    void SetContents(QString s);
    void SetList();

private slots:
    void on_Accept_clicked();
    void on_Reject_clicked();
    void Success();
    void Failed();
    void ResetList(QString);

private:
    Ui::GroupScheduleAccept *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString Date;
    QString Time;
    QString DOW;
    QString Contents;
    Thread* thr;
};

#endif // GROUPSCHEDULEACCEPT_H
