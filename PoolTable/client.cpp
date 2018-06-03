#include "client.h"

#include <QDebug>
#include <QDataStream>
#include <QVector2D>

Client::Client(QObject *parent) : QObject(parent),
    client(new QUdpSocket(this)), display(new ClientDisplay()),
    set(false)
{

}

void Client::startClient()
{
    if (client->isValid()) return;
    client->bind(8081);
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
    QString command;
    stream >> command;
    if (command == "INIT") {
        display->start(stream, *this);
    } else if (command == "BROADCAST") {
        if (!set)
        {
            set = true;
            pair = qMakePair(sender, port);
        }
    } else if (command == "UNDO") {
        emit undo(stream);
    } else if (command == "HIT") {
        emit hit(stream);
    }

}

void Client::joinGame()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << QString("INIT");
    client->writeDatagram(buffer, pair.first, pair.second);
}

void Client::writeMessage(QByteArray data)
{
    client->writeDatagram(data, pair.first, pair.second);
}

Client::~Client()
{
    if (client) delete client;
    if (display) delete display;
}
