#include "timethread.h"

TimeThread::TimeThread(QObject *parent) :
    QThread(parent)
{

}

TimeThread::~TimeThread() {

}

void TimeThread::SetId(string i) {Id = i;}
void TimeThread::SetSocket(SOCKET s) {Server = s;}

void TimeThread::run() {

    qRegisterMetaType<std::string>("string");
    QString strLine;
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString strUnicodeLine;
    QString mess;
    while(1) {
        qDebug("hi");
        recv(Server, buf, MAX_BUFFER_SIZE, 0);
        strLine = buf;
        string ms = buf;
        string code = buf;
        code = code.substr(0,3);
        qDebug(code.c_str());
        if(strcmp(code.c_str(),"000")==0){
            emit TodayEnd();
        }
        else if(strcmp(code.c_str(),"001")==0){
            strLine.remove(0,4);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            emit DailySchedulSend(strUnicodeLine);
        }
        else if(strcmp(code.c_str(),"002")==0){

        }
        else if(strcmp(code.c_str(),"003")==0){
            strLine.remove(0,4);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            emit WeeklySchedulSend(strUnicodeLine);
        }
        else if(strcmp(code.c_str(),"004")==0){
            emit DailyAddSuccess();
        }
        else if(strcmp(code.c_str(),"005")==0){
            emit DailyAddFailed();
        }
        else if(strcmp(code.c_str(),"006")==0){
            emit WeeklyAddSuccess();
        }
        else if(strcmp(code.c_str(),"007")==0){

        }
        else if(strcmp(code.c_str(),"008")==0){
            strLine.remove(0,4);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            emit WeeklyAddFailedbyDaily(strUnicodeLine);
        }
        else if(strcmp(code.c_str(),"009")==0){
            emit WeeklyAddFailedbyWeek();
        }
        else if(strcmp(code.c_str(),"010")==0){
            strLine.remove(0,4);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            emit WeeklyAddFailedbyGroup(strUnicodeLine);
        }
        else if(strcmp(code.c_str(),"011")==0){
            strLine.remove(0,4);
            strUnicodeLine = codec->toUnicode(strLine.toLocal8Bit());
            emit GroupSchedulSend(strUnicodeLine);
        }
        ZeroMemory(buf, MAX_BUFFER_SIZE);
    }
}
