#include "client.h"

#include <QDebug>
#include <QDataStream>
#include <QVector2D>

Client::Client(QObject *parent) : QObject(parent)
{
    client = new QUdpSocket(this);
}

void Client::startClient()
{
    //hardcoded the port for testing
    client->bind(QHostAddress::LocalHost, 8081);
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

#include <iostream>
using std::cout;
using std::endl;
void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QVector2D a;
    double b;
    bool c;
    stream >> a >> b >> c;
    cout << b << " " << c << endl;
    qDebug() << "read from client";

}

void Client::test()
{

}

Client::~Client()
{
    if (client) delete client;
}
