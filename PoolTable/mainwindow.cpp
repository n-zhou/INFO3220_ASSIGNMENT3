#include "mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(Initializer &init, QWidget *parent) : QMainWindow(parent)
{
    PoolGame *game = init.createPoolgame("../PoolTable/config.json",&w);
    if (!game) return;
    if (!init.isStage3()) {
        w.start(game);
        w.show();
        return;
    }

    widget = new QWidget(this);
    client.startClient();

    //creates the mainwindow GUI
    createFormGroupBox();
    //let widget delete this
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(m_groupBox);
    widget->setLayout(mainLayout);
    this->resize(300, 130);
    this->show();
    this->setCentralWidget(widget);


}

void MainWindow::createFormGroupBox()
{
    m_groupBox = new QGroupBox;
    layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Available Games"), new QLabel(tr("\tAction"))));
    QPushButton *hostButton = new QPushButton(tr("Host"));
    connect(hostButton, &QPushButton::pressed, &server, &Server::startServer);
    layout->addRow(new QLabel(tr("Host a new game?")), hostButton);
    QPushButton *button = new QPushButton("Join");
    connect(button, SIGNAL(pressed()), &client, SLOT(joinGame()));
    layout->addRow(new QLabel(tr("Some Game")), button);

    m_groupBox->setLayout(layout);
}

void MainWindow::addNewServer()
{

}



MainWindow::~MainWindow()
{
    if (layout) delete layout;
    if (m_groupBox) delete m_groupBox;
    if (widget) delete widget;
}
