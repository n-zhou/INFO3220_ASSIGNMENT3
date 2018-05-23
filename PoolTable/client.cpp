#include "client.h"

#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    client = new QUdpSocket(this);
}

void Client::startClient()
{
    //hardcoded the port for testing
    client->connectToHost(QHostAddress::LocalHost, 8080);
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    qDebug() << buffer;
    qDebug() << "read from client";

}

void Client::test()
{

}

Client::~Client()
{
    if (client) delete client;
}
