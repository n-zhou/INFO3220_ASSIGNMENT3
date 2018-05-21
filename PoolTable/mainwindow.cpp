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
    this->resize(800, 400);
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
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("join")));
    layout->addRow(new QLineEdit("127.0.0.1 8080"), new QPushButton("Host"));
    m_groupBox->setLayout(layout);
}

void MainWindow::addSever()
{
    QPushButton *button = new QPushButton;
    button->setText("Connect");
    std::stringstream ss;
    ss << "\t" << layout->count() << "\t\t" << "localhost" << "\t\t" << 0 << "\t\t0ms\t";
    std::string s = ss.str();
    QLabel *label = new QLabel(tr(s.c_str()));
    layout->insertRow(layout->rowCount()-1, label, button);
}

void MainWindow::newConnection()
{
    socket = server->nextPendingConnection();
    socket->write("hello\n");
    socket->flush();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MainWindow::readyRead()
{
    qDebug() << socket->readAll();
}

MainWindow::~MainWindow()
{

}
