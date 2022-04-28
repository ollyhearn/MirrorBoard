#ifndef CLIENTLOGIC_H
#define CLIENTLOGIC_H

#include <QObject>
#include <QTcpSocket>

class ClientLogic : public QObject
{
    Q_OBJECT
public:
    explicit ClientLogic(QObject *parent = nullptr);

    bool clientConnect(QString ip);
private:
    QTcpSocket *csocket;
    QByteArray data;

signals:

public slots:
    void slotReadyRead();

};

#endif // CLIENTLOGIC_H
