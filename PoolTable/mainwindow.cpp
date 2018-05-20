#include "mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QString>
#include <QStatusBar>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget(this);
    createFormGroupBox();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    m_progressBar = new QProgressBar;
    m_progressBar->setMaximum(100);
    m_progressBar->setMinimum(0);
    mainLayout->addWidget(m_groupBox);
    widget->setLayout(mainLayout);
    this->resize(800, 400);
    this->show();
    this->setCentralWidget(widget);
}

void MainWindow::createFormGroupBox()
{
    m_groupBox = new QGroupBox;
    layout = new QFormLayout;
    layout->addRow(new QLabel(tr("\tServer\t\tHost\t\tPort\t\tlatency\t")), new QLabel(tr("\tAction")));
    layout->addRow(new QLineEdit, new QPushButton("Host"));
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

MainWindow::~MainWindow()
{

}
