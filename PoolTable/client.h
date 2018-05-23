#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

    void startClient();

    void test();

private:
    QUdpSocket *client;

signals:

public slots:
    void readyRead();
};

#endif // CLIENT_H
