#include <QString>
#include "clientdisplay.h"
#include "stage2ball.h"
#include "stage2table.h"
#include "vector"

ClientDisplay::ClientDisplay(double fps, double tps, QWidget *parent) :
    QDialog(parent), m_framerateTimer(new QTimer()), m_timestepTimer(new QTimer()),
    m_fps(fps), m_tps(tps)
{

}

ClientDisplay::~ClientDisplay()
{
    if (m_game) delete m_game;
    if (m_framerateTimer) delete m_framerateTimer;
    if (m_timestepTimer) delete m_timestepTimer;
}

#include <QDebug>
#include <QFile>
void ClientDisplay::start(PoolGame *game)
{
    QFile file("testingfile.dat");
    QDataStream stream(&file);
    qDebug() << file.open(QIODevice::WriteOnly);
    m_game = game;
    stream << *game;
    file.close();
    qDebug() << file.open(QIODevice::ReadOnly);
    stream >> *m_game;

    this->setMinimumSize(m_game->size());
    this->resize(m_game->size());
    connect(m_framerateTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_timestepTimer, SIGNAL(timeout()),this, SLOT(runSimulationStep()));
    m_framerateTimer->start(1000/m_fps);
    m_timestepTimer->start(1000*m_tps);
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
    m_framerateTimer->stop();
    m_timestepTimer->stop();
    delete m_game;
    m_game = reSync(data);
    m_timestepTimer->start();
    m_framerateTimer->start();
}

PoolGame* ClientDisplay::reSync(QDataStream &stream)
{
    //deserialize the table
    Table *table = new Stage2Table();
    table->deserialize(stream);

    //deserialize the balls
    std::vector<Ball*> balls;
    size_t numberOfBalls = 0;
    stream >> numberOfBalls;
    for (size_t i = 0; i < numberOfBalls; ++i) {
        Ball *b;
        QString type;
        stream >> type;
        if (type == "composite") {
            b = new CompositeBall();
        } else if (type == "stage2") {
            b = new SimpleStage2Ball();
        }
        b->deserialize(stream);
        balls.push_back(b);
    }

    return new PoolGame(table, std::move(balls));

}

