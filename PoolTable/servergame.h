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

#include "originator.h"
#include "poolgame.h"
#include "serverdisplay.h"
#include "server.h"

class ServerGame : public PoolGame, public QObject
{
public:
    ServerGame(PoolGame *game, ServerDisplay &display, Server &server);

    ~ServerGame() = default;

    void draw(QPainter &p) override;

private:
    //socket variables
    QUdpSocket *m_socket = nullptr;
    QSet<QPair<QHostAddress, quint16>> *m_ip;

    //mouse and keyboard variables
    QVector2D m_pos;
    bool m_clicked = false;
    int m_indexOfBall = -1;

    //undo states
    QStack<Memento*> m_states;
    Originator m_originator;
    const std::vector<Ball*> m_intitialState;

public slots:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);

    void hit(QDataStream &stream);
    void undo();
};

#endif // SERVERGAME_H
