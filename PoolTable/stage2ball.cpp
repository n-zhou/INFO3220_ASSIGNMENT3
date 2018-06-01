#include "stage2ball.h"
#include <cmath>

void Stage2Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}

void Stage2Ball::serialize(QDataStream &stream) const
{
    Ball::serialize(stream);
    stream << m_strength;
}

void Stage2Ball::deserialize(QDataStream &stream)
{
    Ball::deserialize(stream);
    stream >> m_strength;
}

CompositeBall::~CompositeBall()
{
    for(Ball * b: m_containedBalls)
    {
        delete b;
    }
}

ChangeInPoolGame CompositeBall::changeVelocity(const QVector2D &deltaV)
{
    float energyOfCollision = mass()*deltaV.lengthSquared();
    if(energyOfCollision>m_strength)
    {
        float energyPerBall = energyOfCollision/m_containedBalls.size();
        QVector2D pointOfCollision((-deltaV.normalized())*m_radius);
        //for each component ball
        for(Ball * b: m_containedBalls)
        {
            b->setVelocity(m_velocity + sqrt(energyPerBall/b->mass())*(b->position()-pointOfCollision).normalized());
            b->setPosition(m_position+b->position());
        }
        ChangeInPoolGame change({this},std::move(m_containedBalls));
        m_containedBalls.clear();
        return change;
    }
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

float CompositeBall::mass() const
{
    return m_mass+m_containedMass;
}

void CompositeBall::draw(QPainter &p)
{
    Stage2Ball::draw(p);

    if(drawChildren)
    {
        //recursively draw children, translating the painter
        //so that the children are drawn realative to the parent
        p.translate(m_position.toPointF());
        for(Ball * b: m_containedBalls)
        {
            b->draw(p);
        }
        p.translate(-m_position.toPointF());
    }

}

void CompositeBall::setRadius(float newRadius)
{
    if(m_radius==-1)
        m_radius = newRadius;
    else
    {
        float ratio = newRadius/radius();
        m_radius = newRadius;
        //recursively decrease the radius of children
        for(Ball * b: m_containedBalls)
        {
            b->setRadius(b->radius()*ratio);
            b->setPosition(b->position()*ratio);
        }
    }
}

void CompositeBall::serialize(QDataStream &stream) const
{
    Stage2Ball::serialize(stream);
    stream << m_containedMass << drawChildren;
    stream << m_containedBalls.size();
    for (auto b : m_containedBalls) {
        b->serialize(stream);
    }
}

void CompositeBall::deserialize(QDataStream &stream)
{
    Stage2Ball::deserialize(stream);
    stream >> m_containedMass >> drawChildren;
    size_t numberOfBalls;
    stream >> numberOfBalls;
    for (size_t i = 0; i < numberOfBalls; ++i) {
        QString type;
        stream >> type;
        Ball *ball;
        if (type == "composite") {
            ball = new CompositeBall();
        } else if (type == "stage2") {
            ball = new SimpleStage2Ball();
        }
        ball->deserialize(stream);
        m_containedBalls.push_back(ball);
    }

}

ChangeInPoolGame SimpleStage2Ball::changeVelocity(const QVector2D &deltaV)
{
    if(mass()*deltaV.lengthSquared()>m_strength)
        return ChangeInPoolGame({this});
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

Ball* CompositeBall::clone() const
{
    CompositeBall *ball = new CompositeBall();
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadWrite);
    this->serialize(stream);
    //discard the header since we know it's a compositeball
    QString throwaway;
    stream >> throwaway;
    ball->deserialize(stream);
    return ball;
}

Ball* SimpleStage2Ball::clone() const
{
    SimpleStage2Ball *ball = new SimpleStage2Ball();
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadWrite);
    this->serialize(stream);
    //discard the header since we know it will be a simple stage 2 ball
    QString throwaway;
    stream >> throwaway;
    ball->deserialize(stream);
    return ball;
}

