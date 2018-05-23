#include "server.h"

#include <QVector2D>
#include <QDataStream>
struct P {
    QVector2D a;
    double b;
    bool c;
};

QDataStream& operator<<(QDataStream &stream, const P &p)
{
    stream << p.a << p.b << p.c;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, P &p)
{
    stream >> p.a;
    stream >> p.b;
    stream >> p.c;
    return stream;
}

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

#include <iostream>
using std::cout;
using std::endl;
void Server::readyRead()
{

    QByteArray buffer;
    buffer.resize(server->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    server->readDatagram(buffer.data(), buffer.size(), &sender, &port);

    QDataStream stream(&buffer, QIODevice::ReadOnly);

    P p;
    stream >> p;
    cout << p.b << " " << p.c << endl;
}

void Server::test()
{
    P p = {QVector2D(100, 150), 0.23, true};
    cout << p.b << " " << p.c << endl;
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << p;
    server->writeDatagram(data, QHostAddress::LocalHost, 8080);
}

Server::~Server()
{
    if (server) delete server;
}
