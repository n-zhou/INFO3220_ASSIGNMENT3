#ifndef SERVERGAME_H
#define SERVERGAME_H

#include <QObject>
#include <QPair>
#include <QSet>
#include <QUdpSocket>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QStack>
#include <QByteArray>
#include <QDataStream>
#include <QTimer>

#include "originator.h"
#include "poolgame.h"
#include "serverdisplay.h"
#include "server.h"

/**
 * @brief The ServerGame class is an extension of PoolGame that allows it to communicate with clients.
 *
 * @author Nic Zhou
 * @since Stage3
 */
class ServerGame : public PoolGame, public QObject
{
public:
    ServerGame(PoolGame *game, ServerDisplay &display, Server &server);

    ~ServerGame();

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p) override;

protected:
    //socket variables not owned by this class
    QUdpSocket *m_socket = nullptr;
    //the set of clients that we will write our data to
    QSet<QPair<QHostAddress, quint16>> *m_ip;

    /**
     * @brief m_syncTimer timer used to synchronize to send data to synchronize with the client
     */
    QTimer *m_syncTimer = nullptr;

    //mouse and keyboard variables
    QVector2D m_pos;
    bool m_clicked = false;
    //index of the ball we are hitting
    int m_indexOfBall = -1;

    //undo states
    QStack<Memento*> m_states;
    Originator m_originator;
    //the intial state of the balls as defined in the config file
    const std::vector<Ball*> m_intitialState;

public slots:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);

    /**
     * @brief hit applies the change in velocity to the ball that was hit
     * using the data for a stream
     * @param stream the data that we use figure out which ball was hit and
     * the resultant change in velocity
     */
    virtual void hit(QDataStream &stream);

    /**
     * @brief undo moves back to the previous state
     */
    virtual void undo();

    /**
     * @brief synchronize serializes the balls in the game and sends it to the client.
     */
    virtual void synchronize();
};

#endif // SERVERGAME_H
