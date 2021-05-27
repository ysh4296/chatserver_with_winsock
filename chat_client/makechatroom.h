#ifndef MAKECHATROOM_H
#define MAKECHATROOM_H

#include "tool.h"
#include <QStringList>

namespace Ui {
class MakeChatRoom;
}

class MakeChatRoom : public QDialog
{
    Q_OBJECT

public:
    explicit MakeChatRoom(QWidget *parent = nullptr);
    ~MakeChatRoom();

    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    void SetId(string i);
    string GetId();
    void SetList();
    void SetThread(QThread* t);
    void SetFileList(QFileInfoList q);

private slots:
    void on_MakingChatroom_btn_clicked();

private:
    Ui::MakeChatRoom *ui;
    SOCKET sock;
    string id;
    QFileInfoList Friend_list;
    QDir dir;
    QFile file;
    QThread* thr;
    QFileInfoList filelist;
};

#endif // MAKECHATROOM_H
