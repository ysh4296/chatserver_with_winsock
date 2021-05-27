#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include "tool.h"

class TimeThread : public QThread
{
    Q_OBJECT
public:
    TimeThread(QObject *parent = 0);
    ~TimeThread();
    void SetId(string i);
    void SetSocket(SOCKET s);

private:
    SOCKET Server;
    string Id;
    char buf[MAX_BUFFER_SIZE];
    void run();

signals:
    void TodayEnd();                        //000 오늘보내기끝
    void DailySchedulSend(QString);         //001 일일일정보내기
    void WeeklySchedulSend(QString);        //003 주간일정보내기
    void DailyAddSuccess();                 //004 일정등록성공
    void DailyAddFailed();                  //005 일정등록실패
    void WeeklyAddSuccess();                //006 주간일정등록성공
    void WeeklyAddFailedbyDaily(QString);   //008 주간등록실패일간겹침
    void WeeklyAddFailedbyWeek();           //009 주간등록실패주간겹침
    void WeeklyAddFailedbyGroup(QString);   //010 주간등록실패그룹겸침
    void GroupSchedulSend(QString);         //011 그룹일정보내기
};

#endif // TIMETHREAD_H
