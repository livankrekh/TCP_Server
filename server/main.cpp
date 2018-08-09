#include <QCoreApplication>
#include "mainserver.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication    a(argc, argv);
    MainServer          server;

    if (argc > 1)
        server.startServer(atoi(argv[1]));
    else
        server.startServer(2307);

    return a.exec();
}
