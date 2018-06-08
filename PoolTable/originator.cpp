#include "originator.h"

void Originator::set(std::vector<Ball*> *state)
{
    m_state = state;
}

std::vector<Ball*>* Originator::getState() const
{
    std::vector<Ball*>* state = new std::vector<Ball*>;
    for (auto b: *m_state) state->push_back(b);
    return state;
}

Memento* Originator::saveToMemento()
{
    std::vector<Ball*>* state = new std::vector<Ball*>;
    for (auto b: *m_state) state->push_back(b);
    return new Memento(state);
}

void Originator::restoreFromMemento(Memento *memento)
{
    m_state = const_cast<std::vector<Ball*>*>(memento->getState());
}
