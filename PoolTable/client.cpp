#include "client.h"

#include <QDebug>
#include <QDataStream>
#include <QVector2D>

Client::Client(QObject *parent) : QObject(parent)
{
    client = new QUdpSocket(this);
    display = new ClientDisplay();
}

void Client::startClient()
{
    //hardcoded the port for testing
    client->bind(QHostAddress::LocalHost, 8081);
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    QDataStream stream(&buffer, QIODevice::ReadOnly);


}

void Client::test()
{

}

Client::~Client()
{
    if (client) delete client;
    if (display) delete display;
}
