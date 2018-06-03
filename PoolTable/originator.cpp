#include "originator.h"

void Originator::set(std::vector<Ball*> *state)
{
    m_state = state;
}

std::vector<Ball*>* Originator::getState() const
{
    return m_state;
}

Memento* Originator::saveToMemento()
{
    return new Memento(m_state);
}

void Originator::restoreFromMemento(Memento *memento)
{
    m_state = const_cast<std::vector<Ball*>*>(memento->getState());
}
