#include "signin.h"
#include "ui_signin.h"

Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
}

Signin::~Signin()
{
    delete ui;
}

void Signin::on_Signin_btn_clicked()
{
    QString Id = ui->ID_line->text();
    QString Pw = ui->PW_line->text();
    QMessageBox Msgbox;
    if (Id.isEmpty() || Pw.isEmpty()) {
        if(Id.isEmpty() && !Pw.isEmpty()) {
            Msgbox.setText("Write ID");
            Msgbox.exec();
        }
        else if (!Id.isEmpty() && Pw.isEmpty()) {
            Msgbox.setText("Write PW");
            Msgbox.exec();
        }
        else {
            Msgbox.setText("Write ID & PW");
            Msgbox.exec();
        }
    }
    else {
    string id = Id.toUtf8().constData();
    string pw = Pw.toUtf8().constData();
    char buf[MAX_BUFFER_SIZE];

    send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
    Sleep(10);
    send(sock, pw.c_str(), MAX_BUFFER_SIZE, 0);
    recv(sock, buf, MAX_BUFFER_SIZE, 0);
    if (strcmp(buf, "Successfully finished signin") == 0) {
        Msgbox.setText(buf);
        Msgbox.exec();
        this->close();
    }
    else {
        Msgbox.setText(buf);
        Msgbox.exec();
        this->close();
    }
    }
}

void Signin::closeEvent(QCloseEvent *bar) {
    string id = "SigninClose";
    send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
    bar->accept();
}

void Signin::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Signin::GetSocket() {
    return sock;
}
