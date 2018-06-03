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


class ClientGame : public PoolGame, public QObject
{
public:
    ClientGame(PoolGame *game, ClientDisplay &display, Client &client);

    ~ClientGame() = default;

    void draw(QPainter &p) override;
private:
    //sockets stuff
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

    void hit(QDataStream &stream);
    void undo(QDataStream &stream);
};

#endif // CLIENTGAME_H
