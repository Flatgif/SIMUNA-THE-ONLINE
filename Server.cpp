#include "Server.h"
#include "Client.h"
#include <stdexcept>

Server::Server(int port_)
{
    isClosed = true;
    port = port_;

    // �\�P�b�g�̍쐬
    serverSocket = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw std::runtime_error("�\�P�b�g�쐬���s");
    }
    isClosed = false;

    // �|�[�g�ė��p�̐ݒ�
    int reuseFlag = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseFlag, sizeof(reuseFlag)) == -1) {
        Close();
        throw std::runtime_error("�ė��p�s��");
    }

    // �\�P�b�g�̐ݒ�
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        Close();
        throw std::runtime_error("Failed to bind a server socket.");
    }

    // �\�P�b�g��ڑ��\��Ԃɂ���
    if (listen(serverSocket, SOMAXCONN) == -1) {
        Close();
        throw std::runtime_error("�\�P�b�g�ڑ��s��");
    }
}

Server::~Server()
{
    Close();
}

void Server::Close()
{
    if (isClosed) {
        return;
    }
    closesocket(serverSocket);
    serverSocket = -1;
    isClosed = true;
}

void Server::SetData(Client::MyStruct data)
{
    data_.pos = data.pos;
    data_.dir = data.dir;
    data_.shootFlag = data.shootFlag;
}

Client* Server::Accept()
{
    sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int sock = (int)accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);
    if (sock == -1) {
        Close();
        throw std::runtime_error("�N���C�A���g�̎󂯓���Ɏ��s");
    }
    return new Client(sock, clientAddr);
}

bool Server::Send(int sock, struct Client::MyStruct data, struct sockaddr_in toAddr)
{
    struct Client::MyStruct sendData;

    sendData.pos.x = htonl(data.pos.x);
    sendData.pos.y = htonl(data.pos.y);
    sendData.pos.z = htonl(data.pos.z);

    sendData.dir.x = htonl(data.dir.x);
    sendData.dir.y = htonl(data.dir.y);
    sendData.dir.z = htonl(data.dir.z);

    int tolen = sizeof(toAddr);
    int ret = sendto(sock, (char*)&sendData, sizeof(sendData), 0, (struct sockaddr*)&toAddr, tolen);
    return true;
}

bool Server::Receive(int sock, struct Client::MyStruct* data, struct sockaddr_in* fromAddr)
{
    int fromlen = sizeof(struct sockaddr_in);
    struct Client::MyStruct recvData;

    int ret = recvfrom(sock, (char*)&recvData, sizeof(recvData), 0, (struct sockaddr*)fromAddr, &fromlen);
    data->pos.x = ntohl(recvData.pos.x);
    data->pos.y = ntohl(recvData.pos.y);
    data->pos.z = ntohl(recvData.pos.z);

    data->dir.x = ntohl(recvData.dir.x);
    data->dir.y = ntohl(recvData.dir.y);
    data->dir.z = ntohl(recvData.dir.z);
    return true;
}