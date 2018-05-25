#ifndef SERVERDISPLAY_H
#define SERVERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>

#include "poolgame.h"

class ServerDisplay : public QDialog
{
    Q_OBJECT
public:
    ServerDisplay(QWidget *parent = nullptr);
    ~ServerDisplay();

private:
    PoolGame *m_game = nullptr;
    QTimer *m_framerateTimer = nullptr;
    QTimer *m_timestepTimer = nullptr;
    double m_fps;
    double m_tps;

signals:

public slots:
    void runSimulationStep();

};

#endif // SERVERDISPLAY_H
