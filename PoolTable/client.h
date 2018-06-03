#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QPair>

#include "clientdisplay.h"

class ClientGame;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void startClient();

private:
    QUdpSocket *client = nullptr;
    ClientDisplay *display = nullptr;

    QPair<QHostAddress, quint16> pair;

    friend class ClientGame;

signals:
    void undo(QDataStream &stream);
public slots:
    void readyRead();
    void joinGame();
    void writeMessage(QByteArray data);
};

#endif // CLIENT_H
