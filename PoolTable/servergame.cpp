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
    connect(m_syncTimer,&QTimer::timeout, this, &ServerGame::synchronize);

    //the timer which we will send a resync with the client
    //A higher frequency may result in a bug where the client's balls all disappear with no way to recover except restarting the application
    m_syncTimer->start(3000);

    //store the initial state of the balls
    for (auto b : m_balls) const_cast<std::vector<Ball*>&>(m_intitialState).push_back(b->clone());
}

void ServerGame::draw(QPainter &p)
{
    PoolGame::draw(p);
    if (m_clicked)
    {
        //we draw the line of the ball from the cursor to the cue ball
        p.drawLine(m_balls[m_indexOfBall]->position().toPointF(), m_pos.toPointF());

        //we remove the procedure of mouse tracking if the velocity is no longer 0
        if (m_balls[m_indexOfBall]->velocity().lengthSquared() > 0.001) m_clicked = false;
    }
}

void ServerGame::mousePressed(QMouseEvent *event)
{
    for (size_t i = 0; i < m_balls.size(); ++i) {
        if ((QVector2D(event->pos())-m_balls[i]->position()).length() < m_balls[i]->radius())
        {
            //we set the "cue" ball to the ball that we click on
            m_indexOfBall = i;
            break;
        }
    }

    if (m_indexOfBall > -1)
    {
        if (m_balls[m_indexOfBall]->velocity().lengthSquared() > 0.001) return;

        //if ball is staionary we perform the procedure allow tracking mouse posititon
        m_clicked = true;
        m_pos = QVector2D(event->localPos());
    }
}

void ServerGame::mouseMoved(QMouseEvent *event)
{
    if (m_clicked)
    {
        //update mouse position
        m_pos = QVector2D(event->localPos());
    }
}

void ServerGame::mouseReleased(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_clicked = false;
        m_pos = QVector2D(event->localPos());

        //clone the state of the balls to save to the originator
        std::vector<Ball*> *saveState = new std::vector<Ball*>;
        for (auto b: m_balls) saveState->push_back(b->clone());
        m_originator.set(saveState);
        //create a memento and push it to the stack
        m_states.push(m_originator.saveToMemento());

        //apply the change in velocity to the ball that we git
        Ball *b = m_balls[m_indexOfBall];
        b->setVelocity(1.5*(b->position()-m_pos));

        //inform the clients which ball was hit and the change in velocity
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
    //save the state of the balls to the memento
    std::vector<Ball*> *saveState = new std::vector<Ball*>;
    for (auto b: m_balls) saveState->push_back(b->clone());
    m_originator.set(saveState);
    m_states.push(m_originator.saveToMemento());

    //apply the change in velocity to the ball that was hit according to what the client sent us
    int index = 0;
    QVector2D velocity;
    stream >> index >> velocity;
    if (index == m_indexOfBall) m_clicked = false;
    m_balls[index]->setVelocity(velocity);
}

void ServerGame::undo()
{
    for (auto b: m_balls) delete b;
    m_balls.clear();

    if (m_states.empty())
    {
        //restore the game to the config file stage
        for (auto b: m_intitialState) m_balls.push_back(b->clone());
    }
    else
    {
        //set the game to the previous state
        m_originator.restoreFromMemento(m_states.pop());
        for (auto b: *m_originator.getState()) m_balls.push_back(b->clone());
    }

    //write the change in state to the client
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
    //send the position of the balls to the client so they can resynchronize
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

ServerGame::~ServerGame()
{
    if (m_syncTimer) delete m_syncTimer;

}


