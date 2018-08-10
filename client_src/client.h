#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <iostream>
#include <bitset>
#include <unistd.h>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit    Client();
    void        startSend();
    virtual     ~Client();

    static int                  i;
    static int                  packet;
    static unsigned short int   port;

private slots:
    void timerEnd();
    void onReadReady();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError err);

private:
    QTcpSocket      *socket;
    QString         name;
    QString         adress;
    QDateTime       startTime;
    size_t          data_size;
};

#endif // CLIENT_H
