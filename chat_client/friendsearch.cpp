#include "friendsearch.h"
#include "ui_friendsearch.h"

FriendSearch::FriendSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendSearch)
{
    ui->setupUi(this);    
}

FriendSearch::~FriendSearch()
{
    delete ui;
}

void FriendSearch::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET FriendSearch::GetSocket() {
    return sock;
}

void FriendSearch::SetId(string i) {
    id = i;
}

string FriendSearch::GetId() {
    return id;
}

void FriendSearch::SetThread(QThread* t) {
    thr = t;
}

void FriendSearch::on_pushButton_clicked()
{    
    QObject::disconnect(thr, SIGNAL(NoUser()), this, SLOT(No_user()));
    QObject::disconnect(thr, SIGNAL(FindUser()), this, SLOT(Send_message()));
    QString str = ui->lineEdit->text();
    string str2 = str.toUtf8().constData();
    string msg = "002 " + str2;
    char buf[MAX_BUFFER_SIZE];
    QMessageBox Msgbox;
    string path = "c:/client/" + id + "/FriendsIndex/" + str2 + ".txt";
    QString filepath = QString::fromLocal8Bit(path.c_str());

    if (QFile::exists(filepath)) {
        Msgbox.setText("exist friend");
        Msgbox.exec();
        ui->lineEdit->clear();
    }
    else if (str2 == id) {
        Msgbox.setText("don't enter your id");
        Msgbox.exec();
        ui->lineEdit->clear();
    }
    else {
        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
        ui->lineEdit->clear();
    }

    QObject::connect(thr, SIGNAL(NoUser()),this, SLOT(No_user()));
    QObject::connect(thr, SIGNAL(FindUser()),this, SLOT(Send_message()));

}

void FriendSearch::No_user() {
    QMessageBox Msgbox;
    Msgbox.setText("There are no users");
    Msgbox.exec();
}

void FriendSearch::Send_message() {
    QMessageBox Msgbox;
    Msgbox.setText("Send invite Message");
    Msgbox.exec();
}
