#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"

/**
 * @brief The Originator class is used to create and restore states of a memento. It is used by the game class
 * to save the state of the balls and restore it for undos and redos.
 * @author Nic Zhou
 * @since Stage3
 * @see Memento
 * @see ServerGame
 */
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

    /**
     * @brief set
     * @param state copies the state of the balls
     */
    void set(std::vector<Ball*> *state);

    /**
     * @brief getState
     * @return returns a deep copy of the state which the caretaker is free
     * to modify as whishes
     */
    std::vector<Ball*>* getState() const;

private:
    std::vector<Ball*> *m_state = nullptr;
};

#endif // ORIGINATOR_H
