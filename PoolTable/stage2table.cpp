#include "stage2table.h"
#include "ball.h"

void Stage2Table::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawRect(0,0,m_width,m_height);

    for(Pocket * pocket: m_pockets)
    {
        pocket->draw(p);
    }
}

ChangeInPoolGame Stage2Table::ballCollision(Ball *b)
{
    for(Pocket * p: m_pockets)
    {
        if(p->encompassed(b->position(),b->radius()))
        {
            return ChangeInPoolGame({b});
        }
    }

    //are we outside the bounds horizontally and getting further away?
    //if so reverse x velocity
    if((b->position().x()<b->radius() && b->velocity().x()<0) || (b->position().x()>width()-b->radius() && b->velocity().x()>0))
        return b->changeVelocity(QVector2D(-b->velocity().x()*2,0));

    //same but vertical
    if((b->position().y()<b->radius() && b->velocity().y()<0) || (b->position().y()>height()-b->radius() && b->velocity().y()>0))
       return b->changeVelocity(QVector2D(0,-b->velocity().y()*2));

    return ChangeInPoolGame();
}

void Stage2Table::serialize(QDataStream &stream)
{
    Table::serialize(stream);
    //number of pockets
    stream << m_pockets.size();
    for (auto p : m_pockets) {
        //serialize each pocket
        p->serialize(stream);
    }

}

void Stage2Table::deserialize(QDataStream &stream)
{
    Table::deserialize(stream);
    size_t numberOfPockets = 0;
    //read the number of pockets
    stream >> numberOfPockets;
    for (size_t i = 0; i < numberOfPockets; ++i) {
        Pocket *pocket = new Pocket();
        //deserialize the data to make the pocket
        pocket->deserialize(stream);
        m_pockets.push_back(pocket);
    }
}
