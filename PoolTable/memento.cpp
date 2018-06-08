#include "memento.h"

Memento::Memento(std::vector<Ball*> *state) :
    m_state(state)
{
    //i didn't know the contructor would be this short
}

Memento::~Memento()
{
    //clean up our memory
    if (m_state)
        for (auto b: *m_state) delete b;
}

const std::vector<Ball*> *Memento::getState() const
{
    return m_state;
}
