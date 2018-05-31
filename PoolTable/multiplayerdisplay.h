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

    virtual void mousePressEvent(QMouseEvent *event) {emit mousePressed(event);}

    virtual void mouseReleaseEvent(QMouseEvent *event) {emit mouseReleased(event);}

    virtual void mouseMoveEvent(QMouseEvent *event) {emit mouseMoved(event);}

    virtual void keyPressEvent(QKeyEvent *event) {emit keyPressed(event);}

signals:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);

public slots:
    virtual void runSimulationStep()
    {
        m_game->simulateTimeStep(0.01);
    }
};

#endif // MULTIPLAYERDISPLAY_H
