#include "serverdisplay.h"
#include "initializer.h"

ServerDisplay::ServerDisplay(double fps, double tps, QWidget *parent) :
    QDialog(parent), m_framerateTimer(new QTimer()),
    m_timestepTimer(new QTimer()), m_fps(fps), m_tps(tps)
{

}

ServerDisplay::~ServerDisplay()
{

}

#include <QDebug>
#include <QFile>
void ServerDisplay::start()
{
    //get rid of this
    m_game = Initializer().createPoolgame("../PoolTable/config.json", nullptr);
    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()),this, SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/m_fps);
    m_timestepTimer->start(1000*m_tps);
    this->show();
    QFile file("testing.dat");
    file.open(QIODevice::ReadWrite);
    QDataStream stream(&file);
    serializeGame(stream);

}

QDataStream& ServerDisplay::serializeGame(QDataStream &stream)
{
    stream << *m_game;
    return stream;
}

void ServerDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    m_game->draw(p);
}


void ServerDisplay::runSimulationStep()
{
    m_game->simulateTimeStep(0.01);
}
