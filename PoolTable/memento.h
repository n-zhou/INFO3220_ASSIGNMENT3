#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include "ball.h"

class Originator;

class Memento
{
public:
    ~Memento();

private:
    //make sure only the originator can modify this class
    friend class Originator;

    Memento();

    void setState(std::vector<Ball*> &balls);
    std::vector<Ball*> getState();

private:
    std::vector<Ball*> state;
};

#endif // MEMENTO_H
