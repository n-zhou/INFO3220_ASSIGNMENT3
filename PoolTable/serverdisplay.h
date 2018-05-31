#ifndef SERVERDISPLAY_H
#define SERVERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>
#include "multiplayerdisplay.h"

class ServerDisplay : public MultiplayerDisplay
{
public:
    ServerDisplay(QWidget *parent = nullptr);
    ~ServerDisplay();

    void start();

    QDataStream& serializeGame(QDataStream &stream);

private:


};

#endif // SERVERDISPLAY_H
