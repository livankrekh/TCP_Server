#include "mainserver.hpp"

MainServer::MainServer(QObject *parent) {
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
        qDebug() << QString::fromUtf8("Server has been started!");
        qDebug() << "TCPSocket listen on port " << tcpServer->serverPort();
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
    connect(newReadSocket, SIGNAL(disconnected(QTcpSocket *)), this, SLOT(disconnect_socket(QTcpSocket *)));
    qDebug() << "Client " << newReadSocket->peerAddress() << " is connected by " << newReadSocket->peerPort() << "port";
}

void MainServer::readSocket()
{
    QTcpSocket *users_socket = static_cast<QTcpSocket *>(QObject::sender());
    int         desc = -1;
    char data[10];

    if (!users_socket || users_socket->state() != QTcpSocket::ConnectedState)
        return ;
    bzero(data, 10);
    data[0] = 2;
    desc = users_socket->socketDescriptor();
    qDebug() << "Received data from: " << users_socket->peerAddress() << ":" << users_socket->peerPort();
    qDebug() << users_socket->readAll();

    users_socket->write(data);
    qDebug() << "Send data";

    users_socket->close();
    clients.remove(desc);
}

void MainServer::disconnect_socket(QTcpSocket *host)
{
    qDebug() << "Host " << host->peerAddress() << ":" << host->peerPort() << " disconnected!";
    clients.remove(host->socketDescriptor());
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
