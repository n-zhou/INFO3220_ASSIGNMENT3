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
    int x = 0;
    while(!client->bind(QHostAddress("192.168.0." + x++), 8081));
    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << QString("INIT");
    client->writeDatagram(buffer, QHostAddress("192.168.0.3"), 8080);
}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    qDebug() << sender << port;
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QString command;
    stream >> command;
    qDebug() << command;
    if (command == "INIT") {
        display->start(stream);
    } else if (command == "BROADCAST") {
        qDebug() << "broadcast recieved";
    }

}

void Client::test()
{

}

Client::~Client()
{
    if (client) delete client;
    if (display) delete display;
}
