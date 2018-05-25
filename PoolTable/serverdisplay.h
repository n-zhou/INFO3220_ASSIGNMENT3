#ifndef SERVERDISPLAY_H
#define SERVERDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>

#include "poolgame.h"

class ServerDisplay : public QDialog
{
    Q_OBJECT
public:
    ServerDisplay(double fps = 60, double tps = 0.01, QWidget *parent = nullptr);
    ~ServerDisplay();

    void start();

    QDataStream& serializeGame(QDataStream &stream);

private:
    PoolGame *m_game = nullptr;
    QTimer *m_framerateTimer = nullptr;
    QTimer *m_timestepTimer = nullptr;
    double m_fps;
    double m_tps;

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void runSimulationStep();

};

#endif // SERVERDISPLAY_H
