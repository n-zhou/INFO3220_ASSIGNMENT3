#include "server.h"

#include <QDataStream>
#include <QByteArray>
#include "initializer.h"
#include "poolgame.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent),
    server(new QUdpSocket(this)), display(new ServerDisplay()),
    broadcastTimer(new QTimer())
{

}


void Server::startServer()
{
    qDebug() << "Button Presssed";
    if (server->isValid()) return;
    server->bind(8080);

    if (server->state() == QAbstractSocket::UnconnectedState) throw new std::exception;

    connect(server, SIGNAL(readyRead()), this, SLOT(readyRead()));
    display->start();
    broadcastTimer->start(2500);
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
        clientSet.insert(qMakePair(sender, port));
        //SENDS THE DATA OF THE GAME TO THE CLIENT
        writeStream << QString("INIT");
        display->serializeGame(writeStream);
        server->writeDatagram(data, sender, port);
        //we found a client so we stop broadcasting
        broadcastTimer->stop();
    } else if (command == "BROADCAST") {
        qDebug() << "we wrote back to ourselves like idiots";
    } else if (command == "STOP") {
        clientSet.remove(qMakePair(sender, port));
        //the client decided to leave the game so we start broadcasting for a new client
        broadcastTimer->start();
    }
}

void Server::broadcast()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << QString("BROADCAST");
    for (quint16 i = 0; i < 257; ++i) {
        //192.168.0.x is the default private IP address of most devices
        server->writeDatagram(buffer, QHostAddress(QString("192.168.0.") + QString::number(i)), 8081);

        /* write to uni localaddress or else devices at uni wont be able to pick us up.
         * NOTE: this list is incomplete. we cannot determine every device at uni. */
        server->writeDatagram(buffer, QHostAddress(QString("10.19.203.") + QString::number(i)), 8081);
        server->writeDatagram(buffer, QHostAddress(QString("10.70.12.") + QString::number(i)), 8081);
    }
}

void Server::setGame(PoolGame *game)
{

}

Server::~Server()
{
    if (server) delete server;
}


