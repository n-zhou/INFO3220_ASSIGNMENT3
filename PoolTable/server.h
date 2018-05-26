#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QPair>
#include <QTimer>

#include "serverdisplay.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    void startServer();

    void test();

private:
    QUdpSocket *server = nullptr;
    ServerDisplay *display = nullptr;
    QTimer *broadcastTimer = nullptr;
    QPair<QHostAddress, quint16> pair;

signals:

public slots:
    void readyRead();
    void broadcast();
};

#endif // SERVER_H
