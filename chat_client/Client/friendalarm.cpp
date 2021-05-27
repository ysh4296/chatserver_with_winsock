#include "friendalarm.h"
#include "ui_friendalarm.h"
#include <Windows.h>

FriendAlarm::FriendAlarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendAlarm)
{
    ui->setupUi(this);
}

FriendAlarm::~FriendAlarm()
{
    delete ui;
}

void FriendAlarm::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET FriendAlarm::GetSocket() {
    return sock;
}

void FriendAlarm::SetId(string i) {
    id = i;
}

string FriendAlarm::GetId() {
    return id;
}


void FriendAlarm::SetThread(QThread* t) {
    thr = t;
}

void FriendAlarm::SetList() {

    string path = "c:/client/" + id + "/InviteAlarm";
    QString InviteFilePath = QString::fromStdString(path);
    dir = InviteFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    ui->NewFriend_list->clear();
    NewFriend_list = dir.entryInfoList();
    for (int i = 0; i < NewFriend_list.size(); i++) {
    QFileInfo root = NewFriend_list.at(i);
    ui->NewFriend_list->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }
}

void FriendAlarm::on_Accept_btn_clicked() {
    QString str = ui->NewFriend_list->currentItem()->text();
    string f_id = str.toUtf8().constData();
    string msg = "003 " + f_id;

    string filepath = "C:/client/" + id +"/InviteAlarm/" + f_id + ".txt";
    string Friendfilepath =  "C:/client/" + id +"/FriendsIndex/" + f_id + ".txt";

    ofstream Write(Friendfilepath, ios::app);
    ifstream Read(filepath);
    if (Write.is_open() && Read.is_open()) {
        string message;
        getline(Read, message);
        while (!Read.eof()) {
            Write << message << endl;
            getline(Read, message);
        }
        Write.close();
        Read.close();
    }

    remove(filepath.c_str());

    SetList();

    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

 //   emit reset();
}

void FriendAlarm::on_Reject_btn_clicked() {
    QString str = ui->NewFriend_list->currentItem()->text();
    string f_id = str.toUtf8().constData();
    string msg = "001 " + f_id;
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);

    string filepath = "C:/client/" + id +"/InviteAlarm/" + f_id + ".txt";
    remove(filepath.c_str());

    SetList();
}
