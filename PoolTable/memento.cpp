#include "memento.h"

Memento::Memento(std::vector<Ball*> *state) :
    state(state)
{

}

Memento::~Memento()
{
    if (state)
        for (auto b: *state) delete b;
}

const std::vector<Ball*> *Memento::getState()
{
    return state;
}
