#include "clientdisplay.h"
#include <QString>

ClientDisplay::ClientDisplay(QWidget *parent) :
    MultiplayerDisplay(parent)
{

}

ClientDisplay::~ClientDisplay()
{

}

void ClientDisplay::start(QDataStream &stream)
{
    m_game = new PoolGame;
    stream >> *m_game;
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()),this, SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/m_fps);
    m_timestepTimer->start(1000*m_tps);
    this->show();
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

