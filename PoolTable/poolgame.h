#ifndef POOLGAME_H
#define POOLGAME_H

#include <vector>
#include <QPainter>
#include <QSize>
#include <QDataStream>

#include "table.h"
#include "ball.h"

#include "changeinpoolgame.h"

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame default constructor added to avoid telescoping in stage3
     */
    PoolGame(){}

    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * m_table,std::vector<Ball*> balls)
        :m_table(m_table),m_balls(balls)
    {}

    virtual ~PoolGame();

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    virtual void simulateTimeStep(float timeStep);

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    virtual void draw(QPainter &p);

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size(){return QSize(m_table->width(),m_table->height());}

    friend QDataStream& operator<<(QDataStream &stream, const PoolGame &game);

    friend QDataStream& operator>>(QDataStream &stream, PoolGame &game);
protected:
    /**
     * @brief collide two balls if they are in contact
     * @param b1
     * @param b2
     * @return the change in the pool game after the collision
     */
    ChangeInPoolGame collide(Ball *b1, Ball *b2);

    Table * m_table = nullptr;
    std::vector<Ball*> m_balls;
};

QDataStream& operator<<(QDataStream &stream, const PoolGame &game);

QDataStream& operator>>(QDataStream &stream, PoolGame &game);

#endif // POOLGAME_H
