#include "clientgame.h"
#include "stage2ball.h"

ClientGame::ClientGame(PoolGame *game, ClientDisplay &display, Client &client) :
    PoolGame(*game), m_socket(client.client), m_serverIP(&client.pair)
{
    connect(&display,&ClientDisplay::mousePressed,this,&ClientGame::mousePressed);
    connect(&display,&ClientDisplay::mouseMoved,this,&ClientGame::mouseMoved);
    connect(&display,&ClientDisplay::mouseReleased,this,&ClientGame::mouseReleased);
    connect(&display,&ClientDisplay::keyPressed,this,&ClientGame::keyPressed);

    connect(&client, &Client::undo,this,&ClientGame::undo);
    connect(&client, &Client::hit,this,&ClientGame::hit);
}

void ClientGame::draw(QPainter &p)
{
    PoolGame::draw(p);
    if (m_clicked)
    {
        p.drawLine(m_balls[m_indexOfBall]->position().toPointF(), m_pos.toPointF());
    }
}

void ClientGame::mousePressed(QMouseEvent *event)
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

void ClientGame::mouseMoved(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_pos = QVector2D(event->localPos());
    }
}

void ClientGame::mouseReleased(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_clicked = false;
        m_pos = QVector2D(event->localPos());
        Ball *b = m_balls[m_indexOfBall];
        b->setVelocity(1.5*(b->position()-m_pos));

        QByteArray buffer;
        QDataStream stream(&buffer, QIODevice::ReadWrite);
        stream << QString("HIT") << m_indexOfBall << b->velocity();
        m_socket->writeDatagram(buffer, m_serverIP->first, m_serverIP->second);
        m_indexOfBall = -1;
    }
}

void ClientGame::keyPressed(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {
        QByteArray buffer;
        QDataStream stream(&buffer, QIODevice::ReadWrite);
        stream << QString("UNDO");
        m_socket->writeDatagram(buffer, m_serverIP->first, m_serverIP->second);
    }
}

void ClientGame::undo(QDataStream &stream)
{
    for (auto b : m_balls) delete b;
    m_balls.clear();
    size_t numberOfBalls = 0;
    stream >> numberOfBalls;
    for (size_t i = 0; i < numberOfBalls; ++i) {
        Ball *ball;
        QString type;
        stream >> type;
        if (type == "composite") {
            ball = new CompositeBall();
        } else if (type == "stage2") {
            ball = new SimpleStage2Ball();
        } else {
            throw new std::invalid_argument("unsupported type");
        }
        ball->deserialize(stream);
        m_balls.push_back(ball);
    }
}

void ClientGame::hit(QDataStream &stream)
{
    int index = 0;
    QVector2D velocity;
    stream >> index >> velocity;
    m_balls[index]->setVelocity(velocity);
}
