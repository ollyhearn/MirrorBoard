#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerLogic : public QTcpServer
{
    Q_OBJECT


public:
    //explicit ServerLogic(QObject *parent = nullptr);
    ServerLogic();
    bool connect();
    QString getIp();


    bool SetPort(long p);
    long getPort();
    void startServer();
signals:

public slots:
    //void incomingConnection(qintptr socketDescriptor);
    //void slotReadyRead();

private:
    QTcpSocket *ssocket;
    QTcpServer *server;
    long port;

    QByteArray data;

};

#endif // SERVERLOGIC_H
