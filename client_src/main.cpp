#include <QCoreApplication>
#include <QTimer>
#include <QTime>
#include "client.h"

int Client::i = 0;
int Client::packet = 0;
unsigned short int Client::port = 2307;

int main(int argc, char *argv[])
{
    QCoreApplication    a(argc, argv);
    QTime               midnight(0,0,0);
    int                 pool_size = 8;
    int                 timeout = 1000;

    if (argc > 1)
        Client::port = atoi(argv[1]);

    if (argc > 2)
    {
        pool_size = atoi(argv[2]);
        if (pool_size <= 0)
            pool_size = 4;
    }

    Client              client_pool[pool_size];
    QTimer              timers[pool_size];

    if (argc > 3)
        timeout = atoi(argv[3]);

    qsrand(midnight.secsTo(QTime::currentTime()));

    for (int i = 0; i < pool_size; i++)
    {
        QObject::connect(&timers[i], SIGNAL(timeout()), &client_pool[i], SLOT(timerEnd()));
        timers[i].start(timeout);
    }

    return a.exec();
}
