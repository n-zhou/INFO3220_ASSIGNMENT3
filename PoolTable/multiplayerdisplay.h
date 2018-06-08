#ifndef MULTIPLAYERDISPLAY_H
#define MULTIPLAYERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include "poolgame.h"
#include <QDebug>

/**
 * @brief The MultiplayerDisplay class is an alternative widget to the Dialog class.
 * Because the Dialog class does not have any virtual methods it is not viable
 * for a networked game. Thus this class serves the purpose of providing a extendable
 * widget for a networked game.
 *
 * @author Nic Zhou
 * @since Stage3
 * @see ClientDisplay
 * @see ServerDisplay
 */
class MultiplayerDisplay : public QDialog
{
    Q_OBJECT

protected:

    /**
     * @brief MultiplayerDisplay protected constructor which only subclasses can instansiate
     * @param parent
     */
    explicit MultiplayerDisplay(QWidget *parent = nullptr) :
        QDialog(parent), m_game(nullptr), m_framerateTimer(new QTimer()),
        m_timestepTimer(new QTimer()), m_fps(60), m_tps(0.01) {}

public:
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

    //methods for capturing mouse and keyboard events that emit a specific signal
    virtual void mousePressEvent(QMouseEvent *event) {emit mousePressed(event);}
    virtual void mouseReleaseEvent(QMouseEvent *event) {emit mouseReleased(event);}
    virtual void mouseMoveEvent(QMouseEvent *event) {emit mouseMoved(event);}
    virtual void keyPressEvent(QKeyEvent *event) {emit keyPressed(event);}
    virtual void keyReleaseEvent(QKeyEvent *event) {emit keyReleased(event);}

signals:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);
    void keyReleased(QKeyEvent *event);
public slots:
    /**
     * @brief runSimulationStep runs the animation step on game
     */
    virtual void runSimulationStep()
    {
        m_game->simulateTimeStep(0.01);
    }
};

#endif // MULTIPLAYERDISPLAY_H
