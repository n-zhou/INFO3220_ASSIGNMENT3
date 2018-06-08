#ifndef SERVERDISPLAY_H
#define SERVERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>
#include "multiplayerdisplay.h"

class Server;

/**
 * @brief The ServerDisplay class is an extension of MultiplayerDisplay. It provides features
 * to handle networking. The ServerDisplay wraps the PoolGame member in the base class with
 * ServerGame.
 *
 * @author Nic Zhou
 * @since Stage3
 * @see Server
 * @see ServerGame
 */
class ServerDisplay : public MultiplayerDisplay
{
public:
    ServerDisplay(QWidget *parent = nullptr);
    ~ServerDisplay();

    /**
     * @brief start initializes the game with
     * @param server the Server which we will initialize the game with
     * @see Server
     */
    void start(Server &server);

    /**
     * @brief serializeGame serializes the game
     * @param stream the QDataStream used to serialized the game
     * @return the serialized game in a QDataStream form
     */
    QDataStream& serializeGame(QDataStream &stream) const;
};

#endif // SERVERDISPLAY_H
