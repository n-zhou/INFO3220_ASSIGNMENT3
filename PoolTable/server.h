#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QSet>
#include <QPair>

#include "serverdisplay.h"

class ServerGame;

/**
 * @brief The Server class is used to broadcast the existence of a PoolGame.
 *
 * @author Nic Zhou
 * @since Stage3
 */
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

protected:
    /**
     * @brief m_socket the socket which the server is binded to
     */
    QUdpSocket *m_socket = nullptr;

    /**
     * @brief display is used to display the host game
     */
    ServerDisplay *display = nullptr;

    /**
     * @brief broadcastTimer the timer used to control how often a broadcast is sent
     */
    QTimer *broadcastTimer = nullptr;

    /**
     * @brief clientSet the set of clients that have acknoweledged our broadcast
     */
    QSet<QPair<QHostAddress, quint16>> clientSet;

    friend class ServerGame;
signals:
    void undo();
    void hit(QDataStream &stream);
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
