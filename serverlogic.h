#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerLogic : public QObject
{
    Q_OBJECT


public:
    explicit ServerLogic(QObject *parent = nullptr);
    bool connect();
    QString getIp();


    bool SetPort(long p);
    long getPort();
signals:

public slots:

private:
    QTcpSocket *ssocket;
    QTcpServer *server;
    long port;

};

#endif // SERVERLOGIC_H
