#include "serverdisplay.h"
#include "initializer.h"
#include <QDebug>

ServerDisplay::ServerDisplay(QWidget *parent) :
    MultiplayerDisplay(parent)
{

}

ServerDisplay::~ServerDisplay()
{
    if (m_game) delete m_game;
}

void ServerDisplay::start()
{

    if (m_game) return;

    m_game = Initializer().createPoolgame("../PoolTable/config.json", nullptr);
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()),this, SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/m_fps);
    m_timestepTimer->start(1000*m_tps);
    this->show();

}

QDataStream& ServerDisplay::serializeGame(QDataStream &stream) const
{
    stream << *m_game;
    return stream;
}
