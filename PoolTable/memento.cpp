#include "memento.h"

Memento::Memento(std::vector<Ball*> *state) :
    state(state)
{
    //i didn't know the contructor would be this short
}

Memento::~Memento()
{
    //clean up our memory
    if (state)
        for (auto b: *state) delete b;
}

const std::vector<Ball*> *Memento::getState() const
{
    return state;
}
