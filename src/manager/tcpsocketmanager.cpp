#include "tcpsocketmanager.h"

#include "src/tcpsocket/tcpclient.h"
#include "src/config/config.h"


extern Config*mainSystemConfig;

TcpSocketManager::TcpSocketManager()
{
}

void TcpSocketManager::sendMessage(QString msg)
{
    this->tcpClient->sendMessage(msg);
}

void TcpSocketManager::doGetMessage(QString msg)
{
    qDebug()<<"get msg:"<<msg;
}

void TcpSocketManager::dpTcpSendMessage(QString msg)
{
    tcpClient->sendMessage(msg);
}

void TcpSocketManager::stop()
{
    tcpClient->closeConnect();
}

int TcpSocketManager::init()
{
    this->tcpClient=new TcpClient(mainSystemConfig->tSocketAddr,mainSystemConfig->tSocketPort);

    //connect(tcpClient,SIGNAL(error(QString)),this,SLOT(doTcpConnectErr(QString)));
    connect(tcpClient,SIGNAL(connected()),this,SIGNAL(connected()));
    connect(tcpClient,SIGNAL(disConnected()),this,SIGNAL(disConnected()));
    connect(tcpClient,SIGNAL(getMessage(QString)),this,SLOT(doGetMessage(QString)));

    return 1;

}

void TcpSocketManager::work()
{
    tcpClient->connectServer();
}
