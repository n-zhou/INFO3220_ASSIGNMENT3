#ifndef POOLGAMEDECORATOR_H
#define POOLGAMEDECORATOR_H

#include <QObject>
#include <QVector2D>
#include <QMouseEvent>
#include <QKeyEvent>
#include "poolgame.h"

class PoolGameDecorator : public QObject, public PoolGame
{
    Q_OBJECT
public:
    PoolGameDecorator();

    ~PoolGameDecorator();

private:

signals:

public slots:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);
};

#endif // POOLGAMEDECORATOR_H
