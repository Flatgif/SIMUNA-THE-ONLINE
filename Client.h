#ifndef Client_h
#define Client_h

#include <queue>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <BaseTsd.h>
#include "Engine/Main.cpp"
typedef SSIZE_T ssize_t;

static const int BuffSize = 1024;

class Client
{
    bool        isClosed;
    std::string hostname;
    int         port;
    int         sock;
    char        buffer[BuffSize];
    std::queue<std::string>    bufferedMessages;

public:
    Client(const std::string& hostname, int port, bool useDelay = true);
    Client(int sock, sockaddr_in& clientAddr);
    ~Client();
    struct MyStruct {
        Vec3 pos;	// ˆÊ’u
        Vec3 dir;	// Œü‚¢‚Ä‚é•ûŒü
        bool shootFlag;//Œ‚‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©
    };
    std::string GetRemoteHost() const;
    int         GetRemotePort() const;
    bool        IsConnected() const;
    void        Close();
    bool Receive(int sock, struct MyStruct* data, struct sockaddr_in* fromAddr);
    bool Send(int sock, struct MyStruct data, struct sockaddr_in toAddr);
};

#endif 