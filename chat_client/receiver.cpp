#include "Receiver.h"



Receiver::Receiver(SOCKET client, string Id)
{
}


Receiver::~Receiver()
{
}

int Receiver::Messanger(SOCKET server, string Id) {
    int cnt = 0;
    do {
        char msg[MAX_BUFFER_SIZE];
        ZeroMemory(msg, MAX_BUFFER_SIZE);
        Recv(server, msg);
        string filepath = msg;//get filename.txt
        //띄우기 asd,qwe
        while (strcmp(msg, "endfile") != 0) {
            cout << filepath << endl;//fd.name 출력
            if(cnt ==0)
            filepath = "c:/client/" + Id + "/" + filepath;
            else if(cnt == 1)
            filepath = "c:/client/" + Id + "/ChatAlarm/" + filepath;
            else if(cnt == 2)
            filepath = "c:/client/" + Id + "/InviteAlarm/" + filepath;
            else if(cnt == 3)
            filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;
            else if(cnt == 4)
            filepath = "c:/client/" + Id + "/FriendsIndex/" + filepath;// 새친구를 표현해줌
            Recv(server, msg);//total byte size
            int totalbytes = atoi(msg);
            FILE *fp = fopen(filepath.c_str(), "wb");
            int left = totalbytes;
            while (1) {
                if (left <= MAX_BUFFER_SIZE) {//파일크기가 MAX_BUFFER_SIZE 보다 작을때
                    Recv(server, msg);
                    fwrite(msg, 1, left, fp);
                    left = 0;
                }
                else if (left > MAX_BUFFER_SIZE) {
                    Recv(server, msg);
                    fwrite(msg, 1, MAX_BUFFER_SIZE, fp);
                    left -= MAX_BUFFER_SIZE;
                }
                if (left == 0) {
                    break;
                }
            }
            fclose(fp);
            if (left == 0) {

                printf("filename %s file receive succeed.\n", msg);
            }
            else {
                cout << QString::fromUtf8("파일을 제대로 받지 못했습니다.").toLocal8Bit().constData() << endl;
            }
            Recv(server, msg);//get filename.txt
            filepath = msg;
        }
        if (strcmp(msg, "endfile") == 0) {

            cout << QString::fromUtf8("채팅 목록 불러오기 완료").toLocal8Bit().constData() << endl;
        }
        cnt++;
    } while (cnt <= 4);
    return 0;
}
int Receiver::Newmsg(SOCKET server, string Id, string file, string message) {
    string filepath = "c:/client/" + Id + "/ChatAlarm/" + file + ".txt";
    ofstream Write(filepath, ios::app);
    if (Write.is_open()) {
        cout << "writing file" << endl;
        Write << message << endl;
    }
    Write.close();
    return 0;
}
string Receiver::Get(SOCKET server, string Id, char* buf) {
    int Bytein = recv(server, buf, MAX_BUFFER_SIZE, 0);
    string code = buf;
    code = code.substr(0, 3);
    if (strcmp(code.c_str(), "000")==0) {
        Messanger(server, Id);
        return "receive complete";
    }
    else if (strcmp(code.c_str(), "006") == 0) {//message 받음 //만약 현제 client가 해당 채팅창에 접속중
        strtok(buf, " ");
        char* ptr = strtok(NULL, " ");
        string file = (strcpy, ptr);
        ptr = strtok(NULL, " ");
        string sender = (strcpy, ptr);
        char Str[MAX_BUFFER_SIZE];
        string tokmsg;
        strcpy(Str, "");
        while (ptr != NULL) {
            strcat(Str,ptr);
            tokmsg = strcat(Str, " ");
            ptr = strtok(NULL, " ");
        }
        Newmsg(server, Id, file, tokmsg); return buf;
    }
    else if (strcmp(code.c_str(), "007") == 0) {//Invite 받음
        strtok(buf, " ");
        char* Invite_id = strtok(NULL, " ");
        string filepath = "c:/client/" + Id + "/InviteAlarm/" + Invite_id + ".txt";
        ofstream Write(filepath, ios::app);
        if (Write.is_open()) {
            cout << "writingfile:" + filepath << endl;
            Write << Invite_id <<endl;
        }
        Write.close();
    }
    else if (strcmp(code.c_str(), "008") == 0) {//새친구의 알람
        strtok(buf, " ");
        char* new_friend = strtok(NULL, " ");
        string filepath = "c:/client/" + Id + "/FriendsIndex/" + new_friend + ".txt";//friends Alarm으로 가지않음.
        //이 친구는 새친구입니다.
        ofstream Write(filepath, ios::app);
        if (Write.is_open()) {
            cout << "writingfile:" + filepath << endl;
            Write << new_friend << endl;
        }
        Write.close();
    }
    else if (Bytein <= 0) {
        exit(0);
        return "error";
    }
    else {
        return buf;
    }
}
int Receiver::Recv(SOCKET client, char* buf) {

    ZeroMemory(buf, MAX_BUFFER_SIZE);
    int Bytein = recv(client, buf, MAX_BUFFER_SIZE, 0);//error handle
    if (Bytein <= 0) {
        return -1;
    }
    else {
        return 1;
    }
}
