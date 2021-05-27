#ifndef GROUPSCHEDULEADD_H
#define GROUPSCHEDULEADD_H

#include "tool.h"

namespace Ui {
class GroupScheduleAdd;
}

class GroupScheduleAdd : public QDialog
{
    Q_OBJECT

public:
    explicit GroupScheduleAdd(QWidget *parent = nullptr);
    ~GroupScheduleAdd();
    void SetSocket(SOCKET s);
    void SetId(string i);
    void SetRoomName(string s);
    void SetFilePath(QString q);
    void SetThread(QThread* t);

private slots:
    void on_Add_btn_clicked();
    void Success();
    void Failed();

private:
    Ui::GroupScheduleAdd *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString filepath;
    QThread* thr;
    GroupScheduleAdd* group;
};

#endif // GROUPSCHEDULEADD_H
