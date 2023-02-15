#ifndef Server_h
#define Server_h
#include "Client.h"

class Server
{
    bool    isClosed;
    int     port;
    int     serverSocket;

public:
    Server(int port);
    ~Server();
    void     Close();
    Client::MyStruct data_;
    void SetData(struct Client::MyStruct data);

    bool Send(int sock, struct Client::MyStruct data, struct sockaddr_in toAddr);
    bool Receive(int sock, struct Client::MyStruct* data, struct sockaddr_in* fromAddr);
    Client* Accept();
};

#endif 
