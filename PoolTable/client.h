#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QPair>

#include "clientdisplay.h"

class ClientGame;

/**
 * @brief The Client class is used to detect a broadcast.
 *
 * @author Nic Zhou
 * @since Stage3
 */
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void startClient();

protected:
    /**
     * @brief client the socket which the client is binded to
     */
    QUdpSocket *m_client = nullptr;

    /**
     * @brief display
     */
    ClientDisplay *m_display = nullptr;

    /**
     * @brief pair the ip of the server which we detected the broadcast from
     */
    QPair<QHostAddress, quint16> m_pair;

    /**
     * @brief set a boolean used to see if the client has connected to a specific
     * server
     */
    bool m_set;

    friend class ClientGame;

signals:
    void undo(QDataStream &stream);
    void hit(QDataStream &stream);
public slots:
    /**
     * @brief readyRead is fired whenever there is something to be read from the socket
     */
    void readyRead();

    /**
     * @brief joinGame acknowledges a broadcast and display the game
     */
    void joinGame();

    /**
     * @brief writeMessage is fired whenever a special message needs to be written
     * to the server.
     * @param data the QByteArray we will sent to the client
     */
    void writeMessage(QByteArray data);

};

#endif // CLIENT_H
