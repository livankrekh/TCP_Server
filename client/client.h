#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QTime>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit    Client();
    void        startSend();
    virtual     ~Client();

    static int      i;
    static int      packet;

private slots:
    void onReadReady();
    void onConnected();
    void onDisconnected();
    void onError();

private:
    QTcpSocket      *socket;
    QString         name;
    QString         adress;
    unsigned int    port;
    QDateTime       startTime;
    size_t          data_size;
};

#endif // CLIENT_H
