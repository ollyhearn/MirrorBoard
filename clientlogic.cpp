#include "clientlogic.h"
#include "serverlogic.h"


ClientLogic::ClientLogic()
{
    csocket = new QTcpSocket();
    csocket->connect(csocket, &QTcpSocket::readyRead, this, &ClientLogic::slotReadyRead);
    csocket->connect(csocket, &QTcpSocket::disconnected, csocket, &QTcpSocket::deleteLater);
}

void ClientLogic::slotReadyRead()
{
    QDataStream in(csocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(in.status() == QDataStream::Ok){
        QString str;
        in << str;
        //show
    }
}

void ClientLogic::SendToServer(QString str){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << str;
    csocket->write(data);
}

void ClientLogic::SendMessage(QString input){
    SendToServer(input);
}

bool ClientLogic::clientConnect(QString ip){
    if(ip != 0){
        QStringList i = ip.split(":");
        qDebug() << "Got " << i[0] << ":" << i[1];
        try{
            qDebug() << "Tried to connect";
            csocket->connectToHost(i[0], i[1].toLong());
            qDebug() << "Connected to host";
            return true;
            if(csocket->waitForConnected(5000)){
                return true;
            }
            else{
                return false;
            }
        }
        catch(std::exception e){
            qDebug() << "Something went wrong!";
            return false;
        }
    }
    else{
        return false;
    }
}
