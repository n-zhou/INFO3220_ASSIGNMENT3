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
    this->resize(300, 130);
    this->show();
    this->setCentralWidget(widget);

}

void MainWindow::createFormGroupBox()
{
    //FIXME
    m_groupBox = new QGroupBox;
    layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Host\t\tPort\t"), new QLabel(tr("\tAction"))));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("Host")));
    layout->addRow(new QLabel(tr("127.0.0.1\t8080\t")), new QPushButton(tr("Join")));
    m_groupBox->setLayout(layout);
}



MainWindow::~MainWindow()
{

}
