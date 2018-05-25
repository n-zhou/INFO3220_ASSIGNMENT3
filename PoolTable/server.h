#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>

#include "serverdisplay.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    void startServer();

    void stopServer();

    void test();

private:
    QUdpSocket *server = nullptr;
    ServerDisplay *display = nullptr;

signals:

public slots:
    void readyRead();
};

#endif // SERVER_H
