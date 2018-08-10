#include <QCoreApplication>
#include "mainserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication    a(argc, argv);
    QTime               midnight(0,0,0);
    MainServer          server;

    qsrand(midnight.secsTo(QTime::currentTime()));

    if (argc > 1)
        server.startServer(atoi(argv[1]));
    else
        server.startServer(2307);

    return a.exec();
}
