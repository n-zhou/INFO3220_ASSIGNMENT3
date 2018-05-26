#include "server.h"

#include <QDataStream>
#include <QByteArray>
#include "initializer.h"
#include "poolgame.h"


Server::Server(QObject *parent) : QObject(parent),
    server(new QUdpSocket(this)), display(new ServerDisplay()),
    broadcastTimer(new QTimer())
{

}

#include <QDebug>
void Server::startServer()
{
    //we hard code the port for testing purposes
    int x = 0;
    while(!server->bind(QHostAddress("192.168.0." + x++), 8080));
    qDebug() << connect(server, SIGNAL(readyRead()), this, SLOT(readyRead()));
    display->start();
    pair = QPair<QHostAddress, quint16>(QHostAddress("127.0.0.1"), 6969);
    broadcastTimer->start(5000);
    connect(broadcastTimer, SIGNAL(timeout()), this, SLOT(broadcast()));
}

void Server::readyRead()
{

    QByteArray buffer;
    buffer.resize(server->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    server->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    qDebug() << "Server Reading from:" << sender << port;
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QString command;
    stream >> command;
    qDebug() << command;

    QByteArray data;
    QDataStream writeStream(&data, QIODevice::WriteOnly);
    if (command == "INIT") {
        //SENDS THE DATA OF THE GAME TO THE CLIENT
        writeStream << QString("INIT");
        display->serializeGame(writeStream);
        server->writeDatagram(data, sender, port);
        pair = QPair<QHostAddress, quint16>(sender, port);
    } else if (command == "BROADCAST") {
        qDebug() << "we wrote back to ourselves like idiots";
    }
}

void Server::broadcast()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << QString("BROADCAST");
    for (int i = 0; i < 100; ++i) {
        server->writeDatagram(buffer, QHostAddress(QString("192.168.0.").append(i)), 8081);
    }
}

Server::~Server()
{
    if (server) delete server;
}


