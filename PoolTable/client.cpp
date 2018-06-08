#include "client.h"

#include <QDebug>
#include <QDataStream>
#include <QVector2D>

Client::Client(QObject *parent) : QObject(parent),
    m_client(new QUdpSocket(this)), m_display(new ClientDisplay()),
    m_set(false)
{

}

void Client::startClient()
{
    if (m_client->isValid()) return;
    m_client->bind(8081);
    connect(m_client, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

void Client::readyRead()
{
    QByteArray buffer;
    buffer.resize(m_client->pendingDatagramSize());
    QHostAddress sender;
    quint16 port;
    m_client->readDatagram(buffer.data(), buffer.size(), &sender, &port);
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    QString command;
    stream >> command;
    if (command == "INIT") {
        m_display->start(stream, *this);
    } else if (command == "BROADCAST") {
        if (!m_set)
        {
            m_set = true;
            m_pair = qMakePair(sender, port);
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
    m_client->writeDatagram(buffer, m_pair.first, m_pair.second);
}

void Client::writeMessage(QByteArray data)
{
    m_client->writeDatagram(data, m_pair.first, m_pair.second);
}

Client::~Client()
{
    if (m_client) delete m_client;
    if (m_display) delete m_display;
}
