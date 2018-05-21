#include "mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QString>
#include <QStatusBar>
#include <string>
#include <sstream>
#include <QDebug>
#include <QTcpSocket>
#include "testserializable.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    createFormGroupBox();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    widget->setLayout(mainLayout);
    this->resize(300, 130);
    this->show();
    this->setCentralWidget(widget);

    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8080);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void MainWindow::createFormGroupBox()
{
    m_groupBox = new QGroupBox;
    layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Host\t\tPort\t"), new QLabel(tr("\tAction"))));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("Host")));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("Join")));

    m_groupBox->setLayout(layout);
}

void MainWindow::newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void MainWindow::readyRead()
{
    char buffer[1024];
    while (socket->canReadLine()) {
        socket->readLine(buffer, 1024);
        qDebug() << buffer;
    }
}

void MainWindow::disconnected()
{
    socket->close();
    socket = nullptr;
}

void MainWindow::test()
{
    struct Serial f;
    f.s = nullptr;
    f.a = 1;
    f.y = false;

}


MainWindow::~MainWindow()
{
    if (server) delete server;
}
