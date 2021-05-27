#ifndef SIGNIN_H
#define SIGNIN_H

#include "tool.h"

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();
    void SetSocket(SOCKET s);
    SOCKET GetSocket();

private slots:
    void on_Signin_btn_clicked();

private:
    void closeEvent(QCloseEvent *bar);
    Ui::Signin *ui;
    SOCKET sock;
};

#endif // SIGNIN_H
