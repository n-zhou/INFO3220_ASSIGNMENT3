#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include "ball.h"

class Originator;

/**
 * @brief The Memento class stores the state of the balls.
 *
 * @author Nic Zhou
 * @since Stage3
 * @see Originator
 */
class Memento
{
public:
    ~Memento();

private:
    //make sure only the originator can modify this class
    friend class Originator;

    /**
     * @brief Memento
     * @param state
     */
    Memento(std::vector<Ball*> *state);

    /**
     * @brief getState
     * @return the state of the balls
     */
    const std::vector<Ball*>* getState() const;

private:
    const std::vector<Ball*> *state = nullptr;
};

#endif // MEMENTO_H
