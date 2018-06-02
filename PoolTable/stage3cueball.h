#ifndef STAGE3CUEBALL_H
#define STAGE3CUEBALL_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector2D>
#include "balldecorator.h"
#include "multiplayerdisplay.h"

class Stage3CueBall : public QObject, public BallDecorator
{
    Q_OBJECT
public:
    Stage3CueBall(Ball *b);
    Ball* clone() const;

private:
    bool m_clicked;
    QVector2D m_pos;

signals:

public slots:
    void mousePressed(QMouseEvent *event);
    void mouseMoved(QMouseEvent *event);
    void mouseReleased(QMouseEvent *event);
    void keyPressed(QKeyEvent *event);
};


#endif // STAGE3CUEBALL_H
