#include "clientdisplay.h"
#include <QString>

ClientDisplay::ClientDisplay(double fps, double tps, QWidget *parent) :
    QDialog(parent), m_game(new PoolGame()), m_framerateTimer(new QTimer()),
    m_timestepTimer(new QTimer()), m_fps(fps), m_tps(tps)
{

}

ClientDisplay::~ClientDisplay()
{
    if (m_game) delete m_game;
    if (m_framerateTimer) delete m_framerateTimer;
    if (m_timestepTimer) delete m_timestepTimer;
}

#include <QDebug>
void ClientDisplay::start(QDataStream &stream)
{
    stream >> *m_game;
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    qDebug() << m_game->size();
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()),this, SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/m_fps);
    m_timestepTimer->start(1000*m_tps);
    this->show();
}

void ClientDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
}

void ClientDisplay::runSimulationStep()
{
    m_game->simulateTimeStep(0.01);
}

void ClientDisplay::synchronize(QDataStream &data)
{
    //we pause the timers while the we resync the game
    m_framerateTimer->stop();
    m_timestepTimer->stop();
    data >> *m_game;
    //start the timerse again after the game is synced
    m_timestepTimer->start();
    m_framerateTimer->start();
}

