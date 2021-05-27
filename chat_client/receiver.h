#ifndef RECEIVER_H
#define RECEIVER_H

#include "tool.h"

class Receiver
{
private:
    SOCKET server;
    string Id;
    char buf[MAX_BUFFER_SIZE];
public:
    Receiver(SOCKET server, string Id);
    ~Receiver();
    int Messanger(SOCKET server, string Id);
    int Newmsg(SOCKET server,string Id, string file, string message);
    string Get(SOCKET server, string Id, char* buf);
    int Recv(SOCKET client, char* buf);
};

#endif // RECEIVER_H
