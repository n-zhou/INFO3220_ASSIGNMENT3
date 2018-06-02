#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include "dialog.h"
#include "server.h"
#include "client.h"
#include "initializer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Initializer &init, QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief createFormGroupBox creates the gui of the mainwindow
     */
    void createFormGroupBox();

    QWidget *widget = nullptr;
    QGroupBox *m_groupBox = nullptr;
    QFormLayout *layout = nullptr;

    //stuff we don't need to delete
    /**
     * @brief w the dialog box used to display games that are less than stage3
     */
    Dialog w;

    /**
     * @brief server
     */
    Server server;

    /**
     * @brief client
     */
    Client client;


signals:

public slots:

};

#endif // MAINWINDOW_H
