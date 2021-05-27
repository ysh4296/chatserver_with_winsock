#ifndef CHATTING_H
#define CHATTING_H

#include "tool.h"
#include "groupscheduleadd.h"
#include "groupscheduleaccept.h"
#include <QTextCodec>

namespace Ui {
class Chatting;
}

class Chatting : public QDialog
{
    Q_OBJECT

public:
    explicit Chatting(QWidget *parent = nullptr);
    ~Chatting();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetRoomName(string s);
    string GetRoomName();
    void SetFilePath(QString q);
    void SetThread(QThread* t);
    void FileRead();
    void FileMove();


private slots:
    void on_MessageSend_btn_clicked();
    void Msg_Handle();
    void on_GroupScheduleAdd_btn_clicked();
    void on_GroupScheduleList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Chatting *ui;
    SOCKET sock;
    string id;
    string R_Name;
    QString filepath;
    QString Groupmsg;
    QThread* thr;
    GroupScheduleAdd* group;
    GroupScheduleAccept* accept;
};

#endif // CHATTING_H
