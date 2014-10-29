#ifndef TCPSOCKETMANAGER_H
#define TCPSOCKETMANAGER_H

#include <QObject>

#include "basemanager.h"

class TcpClient;


/**
 * tcpsocket 通信管理类，用于主要用于通过wifi于小车进行通讯
 * @brief The TcpSocketManager class
 */
class TcpSocketManager : public BaseManager
{
    Q_OBJECT
public:
    TcpSocketManager();

signals:
    //void tcpDisConnected();
    //void tcpConnected();
public slots:
    void sendMessage(QString msg);
    void dpTcpSendMessage(QString msg);

    void stop();
protected slots:
    void doGetMessage(QString msg);
    int init();
    void work();
private:
    TcpClient*tcpClient;
};

#endif // TCPSOCKETMANAGER_H
