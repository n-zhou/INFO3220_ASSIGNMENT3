#ifndef CLIENTDISPLAY_H
#define CLIENTDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>
#include "multiplayerdisplay.h"

class ClientDisplay : public MultiplayerDisplay
{

public:

    ClientDisplay(QWidget *parent = nullptr);
    ~ClientDisplay();

    void start(QDataStream &stream);

protected:

private:
    void synchronize(QDataStream &data);
};

#endif // CLIENTDISPLAY_H
