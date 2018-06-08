#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QUdpSocket>
#include <QPair>
#include "poolgame.h"
#include "clientdisplay.h"
#include "client.h"

/**
 * @brief The ClientGame class extends PoolGame to be able to played over a game
 * hosted on a Server.
 *
 * @author Nic Zhou
 * @since Stage3
 */
class ClientGame : public PoolGame, public QObject
{
public:
    ClientGame(PoolGame *game, ClientDisplay &display, Client &client);

    ~ClientGame() = default;

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p) override;
private:
    //sockets stuff not owned by this class
    QUdpSocket *m_socket;
    QPair<QHostAddress, quint16> *m_serverIP;

    //mouse stuff
    QVector2D m_pos;
    bool m_clicked = false;
    int m_indexOfBall = -1;

public slots:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);

    /**
     * @brief hit is fired whenever the server requests a ball to be hit
     * @param stream
     */
    void hit(QDataStream &stream);

    /**
     * @brief undo fired whenever the server performs an undo and/or
     * synchronization occurs
     * @param stream
     */
    void undo(QDataStream &stream);
};

#endif // CLIENTGAME_H
