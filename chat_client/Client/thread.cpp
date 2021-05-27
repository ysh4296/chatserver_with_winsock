#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{

}

Thread::~Thread() {

}

void Thread::SetId(string i) {Id = i;}
void Thread::SetSocket(SOCKET s) {Server = s;}

void Thread::run()
{
    QString strLine;
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine;
    QString mess;
    while(1) {
        recv(Server, buf, MAX_BUFFER_SIZE, 0);
        strLine = buf;
        strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
        string ms = buf;
        string code = buf;
        code = code.substr(0,3);
        if(strcmp(code.c_str(),"000")==0){

        }
        else if(strcmp(code.c_str(),"001")==0){
            emit NoUser();
        }
        else if(strcmp(code.c_str(),"002")==0){
            emit FindUser();
        }
        else if(strcmp(code.c_str(),"003")==0){
            emit GroupAddSuccess();
        }
        else if(strcmp(code.c_str(),"004")==0){
            emit GroupAddFailed();
        }
        else if(strcmp(code.c_str(),"005")==0){

        }
        else if(strcmp(code.c_str(),"006")==0){
            strtok(buf, " ");
            char* Str;
            Str = strtok(NULL, " ");
            string filepath = "c:/client/" + Id + "/ChatAlarm/" + Str + ".txt";
            strLine = QString::fromLocal8Bit(ms.c_str());
            qDebug(strLine.toUtf8().constData());
            strLine.remove(0,4);
            mess = strLine;
            mess = mess.split(" ").at(0);
            int a = strLine.indexOf(' ');
            strLine.remove(0, a + 1);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            QString Writefilepath = QString::fromLocal8Bit(filepath.c_str());
            QFile file(Writefilepath);
            file.open(QIODevice::WriteOnly | QIODevice::Append);
            QTextStream stream(&file);
            stream << strUnicodeLine << endl;
            file.close();

            emit Send_Message(mess);
        }
        else if(strcmp(code.c_str(),"007")==0){
            strLine.remove(0,4);
            emit ReceiveInvite(strLine);
        }
        else if(strcmp(code.c_str(),"008")==0){
            strLine.remove(0,4);
            emit AccceptFriend(strLine);
        }
        else if(strcmp(code.c_str(),"009")==0){
            strLine.remove(0,4);
            emit GroupFreeTime(strLine);
        }
        else if(strcmp(code.c_str(),"010")==0){
            strLine.remove(0,4);
            emit GroupMember(strLine);
        }
        ZeroMemory(buf, MAX_BUFFER_SIZE);


    }
}
