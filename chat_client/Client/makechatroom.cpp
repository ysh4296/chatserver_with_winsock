#include "makechatroom.h"
#include "ui_makechatroom.h"

MakeChatRoom::MakeChatRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeChatRoom)
{
    ui->setupUi(this);
    ui->Friends_List->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

MakeChatRoom::~MakeChatRoom()
{
    delete ui;
}

void MakeChatRoom::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET MakeChatRoom::GetSocket() {
    return sock;
}

void MakeChatRoom::SetId(string i) {
    id = i;
}

string MakeChatRoom::GetId() {
    return id;
}

void MakeChatRoom::SetList() {
    string path = "c:/client/" + id + "/FriendsIndex";
    QString friendFilePath = QString::fromStdString(path);
    dir = friendFilePath;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    ui->Friends_List->clear();
    Friend_list = dir.entryInfoList();
    for (int i = 0; i < Friend_list.size(); i++) {
    QFileInfo root = Friend_list.at(i);
    ui->Friends_List->addItem(QString("%1").arg(root.fileName()).replace(".txt", ""));
    }
}

void MakeChatRoom::SetFileList(QFileInfoList q) {
    filelist = q;
}


void MakeChatRoom::SetThread(QThread* t) {
    thr = t;
}

void MakeChatRoom::on_MakingChatroom_btn_clicked()
{
    qRegisterMetaType<std::string>("string");
    QStringList stringList;
    QString ID = QString::fromUtf8(id.c_str());
    stringList.push_front(ID);
    foreach (QListWidgetItem *item, ui->Friends_List->selectedItems())
        stringList << item->text();
    qSort(stringList.begin(), stringList.end());
    QString str = stringList.join(",");
    QString cmp;
    QMessageBox Msgbox;
    for (int i = 0; i < filelist.size(); i++) {
        QFileInfo root = filelist.at(i);
        cmp = root.fileName();
        cmp.truncate(cmp.lastIndexOf('.'));
        if (cmp == str)
            break;
    }

    if (cmp != str) {
        string ids = str.toUtf8().constData();
        string msg = "004 " + ids;

        send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    }
    else {
        Msgbox.setText("Room already exists");
        Msgbox.exec();
    }
    this->close();
}
