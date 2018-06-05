#include "servergame.h"

ServerGame::ServerGame(PoolGame *game, ServerDisplay &display, Server &server) :
    PoolGame(*game),
    m_socket(server.m_socket), m_ip(&server.clientSet), m_syncTimer(new QTimer()), m_pos(),
    m_clicked(false), m_indexOfBall(-1), m_states(), m_originator()
{
    connect(&display,&ServerDisplay::mousePressed,this,&ServerGame::mousePressed);
    connect(&display,&ServerDisplay::mouseMoved,this,&ServerGame::mouseMoved);
    connect(&display,&ServerDisplay::mouseReleased,this,&ServerGame::mouseReleased);
    connect(&display,&ServerDisplay::keyPressed,this,&ServerGame::keyPressed);

    connect(&server, &Server::hit,this,&ServerGame::hit);
    connect(&server, &Server::undo, this, &ServerGame::undo);
    connect(m_syncTimer, SIGNAL(timeout()), this, SLOT(synchronize()));
    m_syncTimer->start(1000);
    for (auto b : m_balls) const_cast<std::vector<Ball*>&>(m_intitialState).push_back(b->clone());
}

void ServerGame::draw(QPainter &p)
{
    PoolGame::draw(p);
    if (m_clicked)
    {
        p.drawLine(m_balls[m_indexOfBall]->position().toPointF(), m_pos.toPointF());
    }
}

void ServerGame::mousePressed(QMouseEvent *event)
{
    for (size_t i = 0; i < m_balls.size(); ++i) {
        if ((QVector2D(event->pos())-m_balls[i]->position()).length() < m_balls[i]->radius())
        {
            m_indexOfBall = i;
            break;
        }
    }

    if (m_indexOfBall > -1)
    {
        if (m_balls[m_indexOfBall]->velocity().lengthSquared() > 0.001) return;
        m_clicked = true;
        m_pos = QVector2D(event->localPos());
    }
}

void ServerGame::mouseMoved(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_pos = QVector2D(event->localPos());
    }
}

void ServerGame::mouseReleased(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_clicked = false;
        m_pos = QVector2D(event->localPos());

        std::vector<Ball*> *saveState = new std::vector<Ball*>;
        for (auto b: m_balls) saveState->push_back(b->clone());

        m_originator.set(saveState);
        m_states.push(m_originator.saveToMemento());

        Ball *b = m_balls[m_indexOfBall];
        b->setVelocity(1.5*(b->position()-m_pos));

        QByteArray buffer;
        QDataStream stream(&buffer, QIODevice::ReadWrite);
        stream << QString("HIT") << m_indexOfBall << b->velocity();
        for (auto pair : *m_ip)
        {
            m_socket->writeDatagram(buffer, pair.first, pair.second);
        }
        m_indexOfBall = -1;
    }
}

void ServerGame::keyPressed(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {
        this->undo();
    }
}

void ServerGame::hit(QDataStream &stream)
{
    std::vector<Ball*> *saveState = new std::vector<Ball*>;
    for (auto b: m_balls) saveState->push_back(b->clone());
    m_originator.set(saveState);
    m_states.push(m_originator.saveToMemento());

    int index = 0;
    QVector2D velocity;
    stream >> index >> velocity;
    m_balls[index]->setVelocity(velocity);
}

void ServerGame::undo()
{
    for (auto b: m_balls) delete b;
    m_balls.clear();
    if (m_states.empty())
    {
        for (auto b: m_intitialState) m_balls.push_back(b->clone());
    }
    else
    {
        m_originator.restoreFromMemento(m_states.pop());
        for (auto b: *m_originator.getState()) m_balls.push_back(b->clone());
    }

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadWrite);
    stream << QString("UNDO");
    stream << m_balls.size();
    for (auto b : m_balls) b->serialize(stream);
    for (auto pair : *m_ip)
    {
        m_socket->writeDatagram(buffer, pair.first, pair.second);
    }
}

void ServerGame::synchronize()
{
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadWrite);
    stream << QString("UNDO");
    stream << m_balls.size();
    for (auto b : m_balls) b->serialize(stream);
    for (auto pair : *m_ip)
    {
        m_socket->writeDatagram(buffer, pair.first, pair.second);
    }
}
