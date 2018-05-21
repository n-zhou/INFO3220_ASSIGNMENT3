#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QProgressBar>
#include <QTcpServer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addSever();
    ~MainWindow();
private:
    void createFormGroupBox();
    QGroupBox *m_groupBox;
    QFormLayout *layout;
    QTcpServer *server;
    QTcpSocket *socket;

signals:

public slots:
    void newConnection();
    void readyRead();

};

#endif // MAINWINDOW_H
