#include "stage3cueball.h"

Stage3CueBall::Stage3CueBall(Ball *b) :
    BallDecorator(b)
{

}


void Stage3CueBall::mousePressed(QMouseEvent *event)
{

    if (false)
    {
        m_clicked = true;
        m_pos = QVector2D(event->localPos());
    }
}

void Stage3CueBall::mouseMoved(QMouseEvent *event)
{
    if (m_clicked)
    {
        m_pos = QVector2D(event->localPos());
    }
}

void Stage3CueBall::mouseReleased(QMouseEvent *event)
{

    if (m_clicked)
    {
        m_clicked = false;

        //save state



        setVelocity(3.5*(m_ball->position()-m_pos));

    }
}

void Stage3CueBall::keyPressed(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {

    }
}

Ball* Stage3CueBall::clone() const
{
    Stage3CueBall *ball = new Stage3CueBall(m_ball->clone());


    return ball;
}

