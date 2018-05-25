#include "server.h"

#include <QDataStream>
#include "initializer.h"
#include "poolgame.h"


Server::Server(QObject *parent) : QObject(parent)
{
    server = new QUdpSocket(this);
}

void Server::startServer()
{
    //we hard code the port for testing purposes
    server->bind(QHostAddress::LocalHost, 8080);
    connect(server, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Server::stopServer()
{
    //hahaha lol
    delete this;
}

void Server::readyRead()
{

    QByteArray buffer;
    buffer.resize(server->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    server->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    QDataStream stream(&buffer, QIODevice::ReadOnly);
}

void Server::test()
{

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    //stream << p;

    server->writeDatagram(data, QHostAddress::LocalHost, 8081);
}

Server::~Server()
{
    if (server) delete server;
}
