#ifndef CLIENTDISPLAY_H
#define CLIENTDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>
#include "multiplayerdisplay.h"

class Client;

/**
 * @brief The ClientDisplay class provides a display for the client that is connected to a game
 * hosted elsewhere.
 *
 * @author Nic Zhou
 * @see ServerDisplay
 */
class ClientDisplay : public MultiplayerDisplay
{

public:

    ClientDisplay(QWidget *parent = nullptr);
    ~ClientDisplay();

    /**
     * @brief start shows the display and displays the game
     * @param stream the stream which we create our game from
     * @param client used to connect slots and signals for the game
     */
    void start(QDataStream &stream, Client &client);

public slots:
    /**
     * @brief synchronize synchronizes the game with the server
     * @param data the stream which we used to sync the game
     */
    void synchronize(QDataStream &data);

};

#endif // CLIENTDISPLAY_H
