    #include "client.h"
#include "ui_client.h"
#include "tool.h"


Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    setWindowTitle("cau-talk");
}

Client::~Client()
{
    delete ui;
}

void Client::on_Signin_btn_clicked()
{
    QString str = ui->Signin_btn->text();
    string msg = str.toUtf8().constData();
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    hide();
    Signin sign;
    sign.setWindowTitle("Sign in");
    sign.SetSocket(GetSocket());
    sign.exec();
    show();
}

void Client::on_Login_btn_clicked()
{
    QString str = ui->Login_btn->text();
    string msg = str.toUtf8().constData();
    char buf[MAX_BUFFER_SIZE];

    QString Id = ui->ID_line->text().trimmed();
    QString Pw = ui->PW_line->text().trimmed();
    string id = Id.toUtf8().constData();
    string pw = Pw.toUtf8().constData();
    ui->ID_line->clear();
    ui->PW_line->clear();

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
        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
        recv(sock, buf, MAX_BUFFER_SIZE, 0);

        if (strcmp(buf, "enter your Id and Password") == 0) {
            Sleep(10);
            send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
                qDebug(id.c_str());
            recv(sock, buf, MAX_BUFFER_SIZE, 0);
            if (strcmp(buf, "enter your Id and Password") == 0) {
                Sleep(10);
                send(sock, pw.c_str(), MAX_BUFFER_SIZE, 0);
                qDebug(pw.c_str());
                recv(sock, buf, MAX_BUFFER_SIZE, 0);
            }
        }

        if (strcmp(buf, "Successfully Login") == 0) {
            Msgbox.setText(buf);

            Msgbox.exec();

            hide();

            string filepath = "c:/client";//로그인하면 파일생성
           _mkdir(filepath.c_str());
           filepath = "c:/client/" + id;//로그인하면 파일생성
           _mkdir(filepath.c_str());
           filepath = "c:/client/" + id + "/ChatAlarm";//로그인하면 파일생성
           _mkdir(filepath.c_str());
           filepath = "c:/client/" + id + "/FriendsIndex";//로그인하면 파일생성
           _mkdir(filepath.c_str());
           filepath = "c:/client/" + id + "/InviteAlarm";//로그인하면 파일생성
           _mkdir(filepath.c_str());



            Timetable time;
            time.setWindowTitle("Time Table");
            time.SetId(id);
            time.SetSocket(GetSocket());
            time.SendtTI();
            time.Thre();
            time.Send000();
            time.exec();

        }
        else {
            Msgbox.setText(buf);
            Msgbox.exec();
        }
    }
}

void Client::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Client::GetSocket() {
    return sock;
}

void Client::keyPressEvent(QKeyEvent *event)
{
    if( (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return))
            on_Login_btn_clicked();
}
