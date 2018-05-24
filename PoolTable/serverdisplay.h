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

signals:

};

#endif // SERVERDISPLAY_H
