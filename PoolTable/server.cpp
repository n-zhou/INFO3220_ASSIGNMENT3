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
    //we hard code the port for testing purposes
    quint16 x = 1;
    //while(!server->bind(QHostAddress(QString("192.168.0.") + QString::number(x++)),
      //                  8080));
    server->bind(8080);
    /*
    for (x = 0; x <= 255; ++x) {
        qDebug() << QString("192.168.0.") + QString::number(x);
        qDebug() << server->state();
        if (server->bind(QHostAddress(QString("192.168.0.") + QString::number(x)),
                         8080)) break;
    }
    if (server->state() == QAbstractSocket::UnconnectedState) {
        for (x = 0; x <= 255; ++x) {
            qDebug() << QString("192.168.0.") + QString::number(x);
            qDebug() << server->state();
            if (server->bind(QHostAddress(QString("10.19.203.") + QString::number(x)),
                             8080)) break;
        }
    }
    */
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
    } else if (command == "BROADCAST") {
        qDebug() << "we wrote back to ourselves like idiots";
    } else if (command == "STOP") {
        clientSet.remove(qMakePair(sender, port));
    }
}

void Server::broadcast()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    stream << QString("BROADCAST");
    for (int i = 0; i < 257; ++i) {
        //write to non uni localaddress
        server->writeDatagram(buffer, QHostAddress(QString("192.168.0.") + QString::number(i)), 8081);

        //write to uni localaddress because or else devices at uni wont be able to pick us up
        server->writeDatagram(buffer, QHostAddress(QString("10.19.203.") + QString::number(i)), 8081);
        server->writeDatagram(buffer, QHostAddress(QString("10.70.12.") + QString::number(i)), 8081);
    }
}

Server::~Server()
{
    if (server) delete server;
}


