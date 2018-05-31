#ifndef MULTIPLAYERDISPLAY_H
#define MULTIPLAYERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include "poolgame.h"
#include <QDebug>

class MultiplayerDisplay : public QDialog
{
    Q_OBJECT

public:

    explicit MultiplayerDisplay(QWidget *parent = nullptr) :
        QDialog(parent), m_game(nullptr), m_framerateTimer(new QTimer()),
        m_timestepTimer(new QTimer()), m_fps(60), m_tps(0.01)
    {

    }

    virtual ~MultiplayerDisplay()
    {
        if (m_game) delete m_game;
        if (m_framerateTimer) delete m_framerateTimer;
        if (m_timestepTimer) delete m_timestepTimer;
    }



protected:
    PoolGame *m_game = nullptr;
    QTimer *m_framerateTimer = nullptr;
    QTimer *m_timestepTimer = nullptr;
    double m_fps;
    double m_tps;

    virtual void paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        m_game->draw(p);
    }

    virtual void mousePressEvent(QMouseEvent *) {}

    virtual void mouseReleaseEvent(QMouseEvent *) {}

    virtual void mouseMoveEvent(QMouseEvent *) {}

    virtual void keyPressEvent(QKeyEvent *) {}

signals:

public slots:
    virtual void runSimulationStep()
    {
        m_game->simulateTimeStep(0.01);
    }
};

#endif // MULTIPLAYERDISPLAY_H
