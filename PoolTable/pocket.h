#ifndef POCKET_H
#define POCKET_H

#include <QPainter>
#include <QVector2D>

/**
 * @brief The Pocket class simply represents a pocket on the table
 */
class Pocket
{
public:

    /**
     * @brief Pocket default constructor added for stage 3 to avoid telescoping
     */
    Pocket()
        : m_position(), m_radius()
    {}

    Pocket(QVector2D pos, float r)
        :m_position(pos),m_radius(r)
    {}
    void draw(QPainter &p);
    bool encompassed(QVector2D circleCentre, float r)
    {
        return (circleCentre-m_position).length() + r < m_radius;
    }

    /**
     * @brief serialize serializes the pocket into bytes
     * @param stream
     */
    void serialize(QDataStream &stream);

    /**
     * @brief deserialize deserializes the data so the object can have attribrutes
     * @param stream
     */
    void deserialize(QDataStream &stream);

private:
    QVector2D m_position;
    float m_radius;
};

#endif // POCKET_H
