#ifndef STAGEONETABLE_H
#define STAGEONETABLE_H

#include <QColor>
#include <QPainter>

#include "table.h"

/**
 * @brief The Stage1Table class is a concrete version of the Table class specific to stage one of the assignment
 */
class Stage1Table : public Table
{
public:
    /**
     * @brief Stage1Table
     * @since Stage 3
     */
    Stage1Table() : Table() {}

    Stage1Table(float width, float height,float friction, const QColor &colour)
        :Table(width,height,friction),m_colour(colour)
    {}

    // Table interface
public:
    /**
     * @brief draw the table, it is just a rectangle of width() and height()
     * with the colour set in the constructor
     * @param p the painter used to draw the table
     */
    void draw(QPainter &p);

    void serialize(QDataStream &stream);

    void deserialize(QDataStream &stream);

private:
    QColor m_colour;

    // Table interface
public:
    ChangeInPoolGame ballCollision(Ball *b);
};

#endif // STAGEONETABLE_H
