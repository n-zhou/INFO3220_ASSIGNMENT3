#ifndef CLIENTDISPLAY_H
#define CLIENTDISPLAY_H

#include <QObject>
#include <QWidget>
#include <QDialog>

class ClientDisplay : public QDialog
{
    Q_OBJECT
public:
    ClientDisplay(QWidget *parent = nullptr);
};

#endif // CLIENTDISPLAY_H
