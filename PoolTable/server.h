#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QSet>
#include <QPair>

#include "serverdisplay.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private:
    QUdpSocket *server = nullptr;
    ServerDisplay *display = nullptr;
    QTimer *broadcastTimer = nullptr;
    QSet<QPair<QHostAddress, quint16>> clientSet;

signals:

public slots:
    /**
     * @brief readyRead should be fired whenever there is data available
     * to read from the socket.
     */
    void readyRead();

    /**
     * @brief broadcast actually performs a multicast to 192.168.0.x
     * where x is [0, 257] on port 8081.
     */
    void broadcast();

    /**
     * @brief startServer starts the server on 192.168.0.x where x is the digit of the last
     * address which we can bind the udp socket to.
     */
    void startServer();

    /**
     * @brief writeMessage broadcasts the message to all the clients
     * @param data
     */
    void writeMessage(QByteArray data);


};

#endif // SERVER_H
