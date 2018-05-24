#include "pocket.h"
void Pocket::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(Qt::black));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}

void Pocket::serialize(QDataStream &stream)
{
    stream << m_position << m_radius;
}

void Pocket::deserialize(QDataStream &stream)
{
    stream >> m_position >> m_radius;
}
