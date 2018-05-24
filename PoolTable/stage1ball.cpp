#include "stage1ball.h"

Stage1Ball::Stage1Ball() : Ball()
{
    Ball::m_type = QString("stage1");
}

void Stage1Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}
