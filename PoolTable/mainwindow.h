#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createFormGroupBox();
    QGroupBox *m_groupBox;
    QFormLayout *layout;

signals:

public slots:


};

#endif // MAINWINDOW_H
