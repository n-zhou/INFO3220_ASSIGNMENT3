#include "dialog.h"

#include <QPainter>
#include <QSize>

constexpr float fps = 60;
constexpr float timeStep = 0.01;

Dialog::Dialog(QWidget *parent)
    :QDialog(parent),m_game(nullptr),m_framerateTimer(new QTimer()),m_timestepTimer(new QTimer())
{


}

void Dialog::start(PoolGame *game)
{
    m_game = game;
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer,SIGNAL(timeout()),this,SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/fps);
    m_timestepTimer->start(1000*timeStep);
    connect(this, &Dialog::keyPressed, this, &Dialog::pauseGame);
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    emit mousePressed(event);
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event);
}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseReleased(event);
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
}

void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    emit keyReleased(event);
}

void Dialog::pauseGame(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Pause) {
        if (m_timestepTimer->isActive()) {
            m_timestepTimer->stop();
        } else {
            m_timestepTimer->start();
        }
    }
}

Dialog::~Dialog()
{
    delete m_game;
    delete m_framerateTimer;
    delete m_timestepTimer;
}

void Dialog::runSimulationStep()
{
    m_game->simulateTimeStep(timeStep);
}
