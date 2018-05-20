#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QProgressBar>

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
    QProgressBar *m_progressBar;
signals:

public slots:


};

#endif // MAINWINDOW_H
