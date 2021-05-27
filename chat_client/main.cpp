#include "client.h"
#include "tool.h"
#include <QApplication>
#include <QObject>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 윈속 초기화
        string ip = "165.194.17.7";
        int port = 4296;
        WSADATA data;
        WORD ver = MAKEWORD(2, 2);
        int wsInit = WSAStartup(ver, &data);

        SOCKET consock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in insock;
        insock.sin_family = AF_INET;
        insock.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &insock.sin_addr);
        int result = connect(consock, (sockaddr*)&insock, sizeof(insock));
        char buf[MAX_BUFFER_SIZE];

        if (result == SOCKET_ERROR)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning!!");
            msgBox.setText("connect Failed");
            msgBox.exec();
            exit(1);
        }

        Client w;
        w.SetSocket(consock);
        w.show();


       return a.exec();
}
