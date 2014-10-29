#include "tcpclient.h"


TcpClient::TcpClient(QString addr, int port)
{

    this->addr=addr;
    this->port=port;

    m_socket = new QTcpSocket(this);

    //读取接受到的数据
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(doReadMsg()));

    //已经连接成功
    connect(m_socket,SIGNAL(connected()),this,SIGNAL(connected()));

    //已经断开连接
    connect(m_socket,SIGNAL(disconnected()),this,SIGNAL(disConnected()));

    //连接异常
    connect(m_socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(doError(QAbstractSocket::SocketError)));

}

void TcpClient::sendMessage(QString msg)
{
    if(!msg.isEmpty()){
        m_socket->write(msg.toUtf8());
    }
}

void TcpClient::connectServer()
{
    m_socket->connectToHost(addr,port);
}

void TcpClient::doReadMsg()
{
    QByteArray qba = m_socket->readAll();

    QString msg(qba);

    emit this->getMessage(msg);

}

void TcpClient::closeConnect()
{
    if(m_socket->state() != 0){
        m_socket->abort();
        m_socket->disconnectFromHost();
    }
}

void TcpClient::doError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<socketError<<":"<<m_socket->errorString();
    closeConnect();
    //emit  this->disConnected();
}


int TcpClient::getPort() const
{
    return port;
}

void TcpClient::setPort(int value)
{
    port = value;
}

QString TcpClient::getAddr() const
{
    return addr;
}

void TcpClient::setAddr(const QString &value)
{
    addr = value;
}





