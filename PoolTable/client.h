#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QPair>

#include "clientdisplay.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void startClient();

    void test();

private:
    QUdpSocket *client = nullptr;
    ClientDisplay *display = nullptr;

signals:

public slots:
    void readyRead();
};

#endif // CLIENT_H
