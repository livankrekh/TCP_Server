#include "client.h"

Client::Client() : adress("127.0.0.1"), port(2307)
{
    this->socket = new QTcpSocket(this);
    this->name = QString("Client ") + QString(Client::i);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onReadReady()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(onError(QAbstractSocket::SocketError)));
    Client::i += 1;
}

void Client::startSend()
{
    socket->connectToHost(name, port);
    this->data_size = qrand() % 9216 + 1024;
    qDebug() << this->name << ": connection...";
}

void Client::onConnected()
{
    char data[this->data_size];

    qDebug() << this->name << ": connected!";
    for (int i = 0; i < this->data_size - 1; i++)
    {
        data[i] = qrand() % 93 + 32;
    }
    data[this->data_size] = 0;
    socket->write(data, data_size);
    qDebug() << this->name << " send next data in " << data_size << " bytes:";
    qDebug() << data;
    startTime = QDateTime::currentDateTime();
}

void Client::onReadReady()
{
    QDateTime   currentTime = QDateTime::currentDateTime();
    QByteArray  data_packet = socket->readAll();

    qDebug() << this->name << " accepted data from packet #" << Client::packet << " (" << currentTime - startTime << " sec)";
    qDebug() << "Data from Packet #" << Client::packet
             << ": ["<< data_packet[0]
             << ", " << data_packet[1]
             << ", " << data_packet[2]
             << ", " << data_packet[3]
             << ", " << data_packet[4]
             << ", " << data_packet[5]
             << ", " << data_packet[6]
             << ", " << data_packet[7]
             << ", " << data_packet[8]
             << ", " << data_packet[9] << "]";
    Client::packet += 1;
    this->startSend();
}

void Client::onDisconnected()
{
    qDebug() << this->name << ": disconnected!";
}

Client::~Client()
{
    delete socket;
}
