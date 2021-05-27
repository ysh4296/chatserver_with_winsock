#include "list.h"
#include "ui_list.h"


List::List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::List)
{
    ui->setupUi(this);
    thr = new Thread(this);
  //alarm = new FriendAlarm(this);


    chat = new Chatting(this);

    QObject::connect(thr, SIGNAL(Send_Message(QString)), this, SLOT(Alarm(QString)));           //006
    QObject::connect(thr, SIGNAL(ReceiveInvite(QString)), this, SLOT(InviteAlarm(QString)));    //007
    QObject::connect(thr, SIGNAL(AccceptFriend(QString)), this, SLOT(ResetList(QString)));      //008
}

List::~List()
{
    thr->terminate();
    thr->quit();
    delete thr;
    delete chat;
    delete ui;
}

void List::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET List::GetSocket() {
    return sock;
}

void List::SetId(string i) {
    id = i;
}

string List::GetId() {
    return id;
}

void List::Receive() {

    Receiver receiver(sock, id);

    receiver.Messanger(sock, id);

    SetList();
}

void List::Thre() {
    thr->SetId(id);
    thr->SetSocket(sock);
    thr->start();
}

void List::SetList() {

    ui->Friend_List->clear();
    ui->Chatroom_List->clear();

    int overlap = 0;
    Friend_list.clear();
    QString friendFilePath = "C:/client/";
    friendFilePath.append(QString::fromStdString(id));
    friendFilePath.append("/FriendsIndex");
    dir = friendFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Friend_list = dir.entryInfoList();
    for (int i = 0; i < Friend_list.size(); i++) {
    QFileInfo root = Friend_list.at(i);
    ui->Friend_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }

    Chat_list.clear();
    QString chatFilePath = "C:/client/";
    chatFilePath.append(QString::fromStdString(id));
    chatFilePath.append("/ChatAlarm");
    dir = chatFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Chat_list = dir.entryInfoList();
    int size = Chat_list.size();
    for (int i = 0; i < Chat_list.size(); i++) {
    QFileInfo root = Chat_list.at(i);
    ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    ui->Chatroom_List->item(i)->setForeground(Qt::blue);
    }
    chatFilePath.truncate(chatFilePath.lastIndexOf(QChar('/')));
    dir = chatFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Chat_list.append(dir.entryInfoList());
    for (int i = size; i < Chat_list.size(); i++) {
    QFileInfo root = Chat_list.at(i);
    Already_Chat.append(Chat_list.at(i));
        if (size) {
            for(int j = 0; j < size; j++) {
                if (Chat_list.at(j).fileName() == root.fileName()) {
                    overlap = 1;
                }
            }
            if (overlap == 0) {
                ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
            }
            overlap = 0;
        }
        else {
            ui->Chatroom_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
        }
    }
}

void List::closeEvent(QCloseEvent *bar) {
    string id = "000";
    send(sock, id.c_str(), MAX_BUFFER_SIZE, 0);
    bar->accept();
}

void List::on_Chatroom_List_itemDoubleClicked(QListWidgetItem *item)
{
    QString filepath;
    filepath = QString("%1").arg(Chat_list.at(ui->Chatroom_List->currentIndex().row()).absoluteFilePath());

    string path = "C:/client/" + id + "/ChatAlarm";
    QString r_name = ui->Chatroom_List->currentItem()->text();
    string str = r_name.toUtf8().constData();
    string msg = "006 " + str;

    //Chatting chat;
    chat->setWindowTitle(r_name);
    chat->SetSocket(sock);
    chat->SetId(id);
    chat->SetThread(thr);
    chat->SetFilePath(filepath);
    chat->SetRoomName(str);
    chat->FileRead();
    filepath.truncate(filepath.lastIndexOf(QChar('/')));
    if (strcmp(filepath.toUtf8().constData(), path.c_str()) == 0) {
        chat->FileMove();
        filepath.truncate(filepath.lastIndexOf(QChar('/')));
        filepath.append("/");
        filepath.append(r_name);
        filepath.append(".txt");
        chat->SetFilePath(filepath);
        chat->FileRead();
        SetList();
        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    }
    chat->show();
}


void List::on_Friendsearch_btn_clicked()
{
    FriendSearch search;
    search.setWindowTitle("Friend Search");
    search.SetSocket(GetSocket());
    search.SetId(GetId());
    search.SetThread(thr);
    search.exec();
}

void List::on_Friendalarm_btn_clicked()
{
    FriendAlarm alarm;
    alarm.setWindowTitle("Friend Alarm");
    alarm.SetSocket(GetSocket());
    alarm.SetId(GetId());
    alarm.SetList();
    alarm.exec();

}

void List::on_MakeChatroom_btn_clicked()
{
    MakeChatRoom make;
    make.setWindowTitle("Make Chat Room");
    make.SetSocket(GetSocket());
    make.SetId(GetId());
    make.SetFileList(Already_Chat);
    make.SetThread(thr);
    make.SetList();
    make.exec();
}

void List::MsgHandle(string str) {
    qDebug(str.c_str());
}

void List::Alarm(QString rname) {
    if(chat->isVisible()) {
        if(strcmp(chat->GetRoomName().c_str(), rname.toUtf8().constData()) == 0) {
            FileMove(chat->GetRoomName());
            chat->FileRead();
            SetList();
        }
        else {
            SetList();
        }
    }
    else {
        SetList();
    }
};

void List::ResetList(QString name) {
    string path = "c:/client/" + id + "/FriendsIndex/" + name.toUtf8().constData() + ".txt";
    QString filepath = QString::fromLocal8Bit(path.c_str());

    QFile file(filepath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << name << endl;
    file.close();

    ui->Friend_List->clear();

    Friend_list.clear();
    QString friendFilePath = "C:/client/";
    friendFilePath.append(QString::fromStdString(id));
    friendFilePath.append("/FriendsIndex");
    dir = friendFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    Friend_list = dir.entryInfoList();
    for (int i = 0; i < Friend_list.size(); i++) {
    QFileInfo root = Friend_list.at(i);
    ui->Friend_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }

    QMessageBox Msgbox;
    Msgbox.setText("Have a new friend");
    Msgbox.exec();
}

void List::InviteAlarm(QString name) {
    string path = "c:/client/" + id + "/InviteAlarm/" + name.toUtf8().constData() + ".txt";
    QString filepath = QString::fromLocal8Bit(path.c_str());

    QFile file(filepath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    stream << name << endl;
    file.close();

    QMessageBox Msgbox;
    Msgbox.setText("New friend invitation");
    Msgbox.exec();
}

void List::FileMove(string name) {
    string chatfilepath = "c:/client/" + id + "/" + name + ".txt";
    string alarmfilepath = "c:/client/" + id + "/ChatAlarm/" + name + ".txt";

    ofstream Write(chatfilepath, ios::app);
    ifstream Read(alarmfilepath);
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
    remove(alarmfilepath.c_str());
}
