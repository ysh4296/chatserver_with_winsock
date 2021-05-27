#include "chatting.h"
#include "ui_chatting.h"

Chatting::Chatting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chatting)
{
    ui->setupUi(this);
    group = new GroupScheduleAdd(this);
    accept = new GroupScheduleAccept(this);
}

Chatting::~Chatting()
{
    delete ui;
}

void Chatting::SetSocket(SOCKET s) {
    sock = s;
}

SOCKET Chatting::GetSocket() {
    return sock;
}

void Chatting::SetId(string i) {
    id = i;
}

string Chatting::GetId() {
    return id;
}

void Chatting::SetRoomName(string s) {
    R_Name = s;
    qDebug(R_Name.c_str());
}

string Chatting::GetRoomName() {
    return R_Name;
}

void Chatting::SetFilePath(QString q) {
    filepath = q;
}

void Chatting::SetThread(QThread *t) {
    thr = t;
}

void Chatting::on_MessageSend_btn_clicked()
{
    QString str = ui->Message_Line->text().toUtf8();
    string contents = str.toLocal8Bit().constData();
    ui->Message_Line->clear();

    string msg = "005 " + R_Name + " " + contents;
    send(sock, msg.c_str(), MAX_BUFFER_SIZE, 0);
    qDebug(msg.c_str());
    QString mess = QString::fromUtf8(id.c_str());
    mess.append(": ");
    mess.append(str);

    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine = codec->toUnicode(mess.toLocal8Bit());
    ui->Chatting_Text->append(strUnicodeLine);

    ui->Chatting_Text->verticalScrollBar()->setValue(ui->Chatting_Text->verticalScrollBar()->maximum());

    QFile file(filepath);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&file);
    stream << strUnicodeLine << endl;
    file.close();
}


void Chatting::FileRead() {
//    ifstream Read(filepath.toLocal8Bit().constData());
//    if (Read.is_open()) {
//        string msg;
//        getline(Read, msg);
//        while (!Read.eof()) {
//            ui->Chatting_Text->append(msg.c_str());
//            getline(Read, msg);
//        }
//        Read.close();
//    }

    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    ui->Chatting_Text->clear();
    ui->GroupScheduleList->clear();
    QTextStream stream(&file);
    while(!stream.atEnd()) {
        QString strLine = stream.readLine();
        QTextCodec *codec = QTextCodec::codecForLocale();
        QString strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
        if (strLine.at(0) == "_") {
            Groupmsg = strLine;
            QString str = Groupmsg.remove(0, Groupmsg.indexOf(" "));
            QString str1 = str.split("____").at(0);
            QString str2 = str.split("____").at(1);
            str1.remove(0,3);
            str1.truncate(str1.lastIndexOf(QChar(' ')));
            str1.truncate(str1.lastIndexOf(QChar(' ')));
            str1.truncate(str1.lastIndexOf(QChar(' ')));
            str = str1 + str2;
            ui->GroupScheduleList->addItem(str);
        }
        else {
            ui->Chatting_Text->append(strUnicodeLine);
        }
    }
    file.close();
}

void Chatting::FileMove() {
    string chatfilepath = "c:/client/" + id + "/" + R_Name + ".txt";
    string alarmfilepath = filepath.toUtf8().constData();

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

void Chatting::Msg_Handle() {
    QMessageBox Msgbox;
    Msgbox.setText("Send invite Message");
    Msgbox.exec();
}

void Chatting::on_GroupScheduleAdd_btn_clicked()
{
    group->SetSocket(sock);
    group->SetId(id);
    group->SetThread(thr);
    group->SetRoomName(R_Name);
    group->SetFilePath(filepath);
    group->setModal(true);
    group->exec();
}

void Chatting::on_GroupScheduleList_itemDoubleClicked(QListWidgetItem *item)
{
    QString str = ui->GroupScheduleList->currentItem()->text();
    QString date = str.split("( ").at(1).split(" | ").at(0);
    QString time = str.split("( ").at(1).split(" | ").at(1);
    QString dow = str.split("( ").at(1).split(" | ").at(2).split(" ").at(0);
    QString contents = str.split(" ").at(2);

    thr->terminate();

    accept->setWindowTitle("Accept");
    accept->SetDate(date);
    accept->SetTime(time);
    accept->SetDOW(dow);
    accept->SetContents(contents);
    accept->SetRoomName(R_Name);
    accept->SetSocket(sock);
    accept->SetId(id);
    accept->SetThread();
    accept->exec();

    thr->start();
}
