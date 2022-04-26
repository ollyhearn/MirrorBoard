#include "serverlogic.h"

ServerLogic::ServerLogic(QObject *parent)
    : QObject{parent}
{
    ssocket = new QTcpSocket(this);
    server = new QTcpServer(this);
    port = 57483;
}

bool ServerLogic::connect(){
    ssocket->connectToHost("mirea.ru", 80); //Подключаемся к сайту МИРЭА
    if( ssocket->waitForConnected(1000)){
        return true;
    }
    else return false;
}

QString ServerLogic::getIp(){
    if (connect()){
        return "IP: " + ssocket->localAddress().toString();
        return "IP: " + server->serverAddress().toString();
        //ssocket->
    }
    else return "Failed to connect!";
}

bool ServerLogic::SetPort(long p){
    if(p > 0 && p < 65535){
        port = p;
        return true;
    }
    else return false;
}

long ServerLogic::getPort(){
    return port;
}
