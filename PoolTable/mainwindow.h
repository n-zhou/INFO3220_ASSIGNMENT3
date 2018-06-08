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

/**
 * @brief The MainWindow class is used to display a widget to host and join a
 * simple networked PoolGame. The buttons are one time use.
 *
 * @author Nic Zhou
 * @since Stage3
 */
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

    //gui layout magic
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

};

#endif // MAINWINDOW_H
