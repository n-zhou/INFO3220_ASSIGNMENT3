#include <QApplication>

#include "mainwindow.h"
#include "initializer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Initializer initializer;
    MainWindow m(initializer);
    return a.exec();
}
