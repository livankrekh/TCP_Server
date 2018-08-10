#include "client.h"

Client::Client() : adress("127.0.0.1"), port(2307)
{
    this->name = QString("Client ") + QString(Client::i);
    Client::i += 1;
}

void Client::startSend()
{
    this->socket = new QTcpSocket(this);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(onError(QAbstractSocket::SocketError)));
    socket->connectToHost(QHostAddress::Any, port);
    this->data_size = qrand() % 9216 + 1024;
    qDebug() << this->name << ": connection...";
}

void Client::onConnected()
{
    char data[this->data_size];

    qDebug()<< "\033[1m\033[32m" << this->name << ": connected!\033[0m";
    for (unsigned int i = 0; i < this->data_size - 1; i++)
    {
        data[i] = qrand() % 93 + 32;
    }
    data[this->data_size] = 0;
    socket->write(data, data_size);
    qDebug() << "\033[1m\033[36m" << this->name << " send next data in " << data_size << " bytes:\033[0m";
    qDebug() << data;
    startTime = QDateTime::currentDateTime();
}

void Client::onReadReady()
{
    QDateTime   currentTime = QDateTime::currentDateTime();
    QByteArray  data_packet = socket->readAll();

    qDebug() << "\033[1m\033[32m" << this->name << " accepted data from packet #"
             << Client::packet << " (" << startTime.msecsTo(currentTime) << " msec)\033[0m";
    qDebug() << "Data from Packet #" << Client::packet
             << ": [" << QString::number(data_packet[0]) << "]";
    Client::packet += 1;
}

void Client::onDisconnected()
{
    qDebug() << this->name << ": disconnected!";
    this->startSend();
}

Client::~Client()
{
    delete socket;
}

void Client::onError(QAbstractSocket::SocketError err)
{
    qDebug() << this->name << ": error in connection!";
    qDebug() << "\033[1m\033[31m" << err << "\033[0m";
}
