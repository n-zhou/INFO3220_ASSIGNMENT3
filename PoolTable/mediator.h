#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

class Mediator : public QObject
{
    Q_OBJECT
public:
    explicit Mediator(QObject *parent = nullptr);

signals:

public slots:

};

#endif // MEDIATOR_H
