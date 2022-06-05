#include "serverlogic.h"


ServerLogic::ServerLogic() : ssocket(new QTcpSocket()), rsocket(new QTcpSocket()), server(new QTcpServer()), port(57483)
{
    connect(rsocket, &QTcpSocket::readyRead, this, &ServerLogic::slotReadyRead);
    connect(rsocket, &QTcpSocket::disconnected, this, &ServerLogic::deleteLater);
}

void ServerLogic::startServer(){
    if(this->listen(QHostAddress::Any, port)){
        qDebug() << "succ";
    }
}

bool ServerLogic::sconnect(){
    startServer();
    ssocket->connectToHost("mirea.ru", 80); //Подключаемся к сайту МИРЭА
    if( ssocket->waitForConnected(1000)){
        return true;
    }
    else return false;

}

QString ServerLogic::getIp(){
    if (sconnect()){
        return ssocket->localAddress().toString();
        //return server->serverAddress().toString();
        //ssocket->
    }
    else return "Failed to connect!";

}

bool ServerLogic::SetPort(long p){
    if(p > 0 && p < 65536){
        port = p;
        return true;
    }
    else return false;
}

long ServerLogic::getPort(){
    return port;
}

void ServerLogic::incomingConnection(qintptr socketDescriptor){
    rsocket->setSocketDescriptor(socketDescriptor);



}

void ServerLogic::slotReadyRead(){
    rsocket = (QTcpSocket*)sender();
    QDataStream in(rsocket);

    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(in.status() == QDataStream::Ok){
        QString got;
        in >> got;
        emit receivedText(got);
    }
}

void ServerLogic::sendToClient(const QString& got){
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << got;
    rsocket->write(data);
}

//void ServerLogic::receivedText(const QString& s){

//}
