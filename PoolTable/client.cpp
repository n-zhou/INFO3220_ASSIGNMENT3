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

}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    qDebug() << "Client Reading From:" << sender << port;
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QString command;
    stream >> command;
    qDebug() << command;
    if (command == "INIT") {
        display->start(stream);
    } else if (command == "BROADCAST") {
        static int done = 0;
        if (!done) {
            QByteArray buffer2;
            QDataStream stream2(&buffer2, QIODevice::WriteOnly);
            stream2 << QString("INIT");
            client->writeDatagram(buffer2, sender, port);
            ++done;
        }
        return;

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
