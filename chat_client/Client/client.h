#ifndef CLIENT_H
#define CLIENT_H
#include "tool.h"
#include "signin.h"
#include "timetable.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();
    Signin* psign;

private slots:
    void on_Signin_btn_clicked();

    void on_Login_btn_clicked();

private:
    void keyPressEvent(QKeyEvent *event);
    Ui::Client *ui;
    SOCKET sock;
};

#endif // CLIENT_H
