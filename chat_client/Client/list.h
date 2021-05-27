#ifndef LIST_H
#define LIST_H

#include "tool.h"
#include "thread.h"
#include "receiver.h"
#include "friendsearch.h"
#include "friendalarm.h"
#include "makechatroom.h"
#include "chatting.h"

namespace Ui {
class List;
}

class List : public QDialog
{
    Q_OBJECT

public:
    explicit List(QWidget *parent = nullptr);
    ~List();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetList();
    void Receive();
    void Thre();

private slots:
    void on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item);
    void on_Friendsearch_btn_clicked();
    void on_Friendalarm_btn_clicked();
    void on_MakeChatroom_btn_clicked();
    void MsgHandle(string str);
    void Alarm(QString);
    void ResetList(QString);
    void InviteAlarm(QString);
    void FileMove(string name);

private:
    void closeEvent(QCloseEvent *bar);
    Ui::List *ui;
    SOCKET sock;
    QFileInfoList Friend_list;
    QFileInfoList Chat_list;
    QFileInfoList Already_Chat;
    QDir dir;
    QFile file;
    string id;
    Thread* thr;
    Chatting* chat;
    FriendAlarm* alarm;
};

#endif // LIST_H
