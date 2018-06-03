#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"

class Originator
{
public:
    Originator() = default;

    ~Originator() = default;

    /**
     * @brief saveToMemento
     * @return
     */
    Memento* saveToMemento();

    /**
     * @brief restoreFromMemento sets the state of the originator to hold the memento's
     * state.
     * @param memento
     */
    void restoreFromMemento(Memento *memento);

    void set(std::vector<Ball*> *state);
    std::vector<Ball*>* getState() const;

private:
    std::vector<Ball*> *m_state = nullptr;
};

#endif // ORIGINATOR_H
