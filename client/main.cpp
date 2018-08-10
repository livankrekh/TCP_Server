#include <QCoreApplication>
#include "client.h"

int Client::i = 0;
int Client::packet = 0;

int main(int argc, char *argv[])
{
    QCoreApplication    a(argc, argv);
    QTime               midnight(0,0,0);
    Client              client_pool[8];

    qsrand(midnight.secsTo(QTime::currentTime()));

    for (int i = 0; i < 8; i++)
    {
        client_pool[i].startSend();
    }

    return a.exec();
}
