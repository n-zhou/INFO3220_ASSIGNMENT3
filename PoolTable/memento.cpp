#include "memento.h"

Memento::Memento()
{

}

Memento::~Memento()
{
    for (auto b: state) delete b;
}

void Memento::setState(std::vector<Ball *> &balls)
{
    for (auto b: balls) state.push_back(b->clone());
}

std::vector<Ball*> Memento::getState()
{
    return std::move(state);
}
