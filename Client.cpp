#include "Client.h"

#include <stdexcept>

#pragma comment( lib, "ws2_32.lib" )


static std::string FormatString(const char* format, ...)
{
    static char buff[1024];
    va_list marker;
    va_start(marker, format);
    vsprintf_s(buff, format, marker);
    va_end(marker);
    return buff;
}


Client::Client(const std::string& hostname_, int port_, bool useDelay)
{
    hostname = hostname_;
    port = port_;
    isClosed = true;

    // ソケットの作成
    sock = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw std::runtime_error("ソケットの作成に失敗");
    }
    isClosed = false;

    if (!useDelay) {
        int noDelay = 1;
        const char* pOpt = (const char*)&noDelay;
        if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, pOpt, sizeof(noDelay)) == -1) {
            Close();
            throw std::runtime_error("オプション設定失敗");
        }
    }

    // ホスト名の解決
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_);
    in_addr addr;
    addr.s_addr = inet_addr(hostname_.c_str());
    if (addr.s_addr == -1) {
        hostent* host = gethostbyname(hostname.c_str());
        if (!host) {
            throw std::runtime_error("ホストが取得できない");
        }
        memcpy(&addr, (in_addr*)*host->h_addr_list, sizeof(in_addr));
    }
    hostname = std::string(inet_ntoa(addr));
    serverAddr.sin_addr = addr;

    // ホストへの接続
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        Close();
        throw std::runtime_error(FormatString("ソケットをサーバーに接続できません %s:%d", hostname.c_str(), port));
    }
}

Client::Client(int sock_, sockaddr_in& clientAddr)
{
    sock = sock_;
    isClosed = false;

    hostname = std::string(inet_ntoa(clientAddr.sin_addr));
    port = ntohs(clientAddr.sin_port);
}

Client::~Client()
{
    Close();
}

std::string Client::GetRemoteHost() const
{
    return hostname;
}

int Client::GetRemotePort() const
{
    return port;
}

void Client::Close()
{
    if (isClosed) {
        return;
    }
    closesocket(sock);
    sock = -1;
}

bool Client::IsConnected() const
{
    return !isClosed;
}

bool Client::Receive(int sock,MyStruct* data,sockaddr_in* fromAddr)
{
    int fromlen = sizeof(sockaddr_in);
    MyStruct recvData;

    int ret = recvfrom(sock, (char*)&recvData, sizeof(recvData), 0, (sockaddr*)fromAddr, &fromlen);
    data->pos.x = ntohl(recvData.pos.x);
    data->pos.y = ntohl(recvData.pos.y);
    data->pos.z = ntohl(recvData.pos.z);

    data->dir.x = ntohl(recvData.dir.x);
    data->dir.y = ntohl(recvData.dir.y);
    data->dir.z = ntohl(recvData.dir.z);
    return true;
}


bool Client::Send(int sock, struct MyStruct data,sockaddr_in toAddr)
{
    struct MyStruct sendData;

    sendData.pos.x = htonl(data.pos.x);
    sendData.pos.y = htonl(data.pos.y);
    sendData.pos.z = htonl(data.pos.z);

    sendData.dir.x = htonl(data.dir.x);
    sendData.dir.y = htonl(data.dir.y);
    sendData.dir.z = htonl(data.dir.z);

    int tolen = sizeof(toAddr);
    int ret = sendto(sock, (char*)&sendData, sizeof(sendData), 0, (sockaddr*)&toAddr, tolen);
    return true;
}

