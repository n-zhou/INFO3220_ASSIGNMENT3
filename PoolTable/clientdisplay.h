#ifndef CLIENTDISPLAY_H
#define CLIENTDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTimer>
#include <QDataStream>
#include "poolgame.h"

class ClientDisplay : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief ClientDisplay
     * @param fps - frames per second
     * @param tps - ticks per second
     * @param parent
     */
    ClientDisplay(double fps = 60, double tps = 0.01, QWidget *parent = nullptr);
    ~ClientDisplay();

    void start(PoolGame *game);

protected:
    void paintEvent(QPaintEvent *);

private:
    PoolGame *m_game = nullptr;
    QTimer *m_framerateTimer = nullptr;
    QTimer *m_timestepTimer = nullptr;
    double m_fps;
    double m_tps;

    PoolGame* reSync(QDataStream &stream);

signals:

public slots:
    void runSimulationStep();
    void synchronize(QDataStream &data);
};

#endif // CLIENTDISPLAY_H
