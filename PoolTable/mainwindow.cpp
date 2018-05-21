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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    createFormGroupBox();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    widget->setLayout(mainLayout);
    this->resize(300, 150);
    this->show();
    this->setCentralWidget(widget);

    server = new QTcpServer;
    server->listen(QHostAddress::Any, 8080);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

void MainWindow::createFormGroupBox()
{
    m_groupBox = new QGroupBox;
    layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Host\t\tPort\t"), new QLabel(tr("\tAction"))));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("Join")));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton("Host"));
    m_groupBox->setLayout(layout);
}

void MainWindow::newConnection()
{
    socket = server->nextPendingConnection();
    socket->write("hello\n");
    socket->flush();
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
}
MainWindow::~MainWindow()
{

}
