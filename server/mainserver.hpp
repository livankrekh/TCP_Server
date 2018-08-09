#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>

class MainServer : public QObject
{
    Q_OBJECT

public:
    explicit MainServer(QObject *parent = nullptr);
    void    startServer(int port);
    virtual ~MainServer();

public slots:
    void newClient();
    void readSocket();
    void disconnect_socket(QTcpSocket *host);

private:
    QTcpServer              *tcpServer;
    QMap<int,QTcpSocket *>  clients;
    unsigned short int      port;
    bool                    status;
};

#endif // MAINSERVER_H
