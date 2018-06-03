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

    Memento(std::vector<Ball*> *state);

    const std::vector<Ball*>* getState();

private:
    const std::vector<Ball*> *state = nullptr;
};

#endif // MEMENTO_H
