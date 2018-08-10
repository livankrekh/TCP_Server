#include "mainserver.hpp"

MainServer::MainServer() {
}

void MainServer::startServer(int port)
{
    this->tcpServer = new QTcpServer(this);
    if (port > 0)
        this->port = port;
    else
        this->port = 2307;
    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
    if (!tcpServer->listen(QHostAddress::Any, port) && this->status == 0)
    {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
    else
    {
        this->status = 1;
        qDebug() << "Server has been started!";
        qDebug() << "\033[1m\033[32mTCPSocketServer listen on port" << tcpServer->serverPort() << "\033[0m";
    }
}

void MainServer::newClient()
{
    QTcpSocket* newReadSocket;
    int         socketDesc;

    if (this->status == false)
        return ;
    newReadSocket = tcpServer->nextPendingConnection();
    socketDesc = newReadSocket->socketDescriptor();
    this->clients[socketDesc] = newReadSocket;
    connect(newReadSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(newReadSocket, SIGNAL(disconnected()), this, SLOT(disconnect_socket()));
    qDebug() << "\033[1m\033[36mClient " << newReadSocket->peerAddress() << " is connected by " << newReadSocket->peerPort() << "port\033[0m";
}

void MainServer::readSocket()
{
    QTcpSocket *users_socket = static_cast<QTcpSocket *>(QObject::sender());
    char data[10];

    if (!users_socket || users_socket->state() != QTcpSocket::ConnectedState)
        return ;
    bzero(data, 10);
    data[0] = 2;
    qDebug() << "\033[1m\033[32mReceived data from: " << users_socket->peerAddress() << ":" << users_socket->peerPort() << "\033[0m";
    qDebug() << users_socket->readAll();

    users_socket->write(data);
    qDebug() << "Send data";

    users_socket->close();
}

void MainServer::disconnect_socket()
{
    foreach(int i, clients.keys())
    {
        if (clients[i]->state() != QTcpSocket::SocketState::ConnectedState && clients[i]->state() != QTcpSocket::SocketState::ConnectingState)
        {
            qDebug() << "\033[1m\033[31mHost #" << i << " is disconnected!\033[0m";
            clients.remove(i);
        }
    }
}

MainServer::~MainServer()
{
    foreach(int i, clients.keys())
    {
        clients[i]->close();
        delete clients[i];
        clients.remove(i);
    }
    tcpServer->close();
    delete tcpServer;
}
