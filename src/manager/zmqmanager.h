#ifndef ZMQMANAGER_H
#define ZMQMANAGER_H


#include "basemanager.h"

#include <QObject>


//运行状态
#define BASE_STATION_CONN_STATUS    "bc1"
#define BASE_STATION_CONN_CAR    "bc2"
#define BASE_STATION_CONN_TOPE   "bc3"
#define BASE_STATION_CONN_SENIOR "bc4"


#define CENTER_SERVER_STATION_CONN_STATUS    "s1"



class BaseClient;
class Message;

class ZmqManager : public BaseManager
{
    Q_OBJECT
public:
    explicit ZmqManager();

signals:
    void carCommand(QString msg);

public slots:
    void sendMessage(QString content);

    //定点发送消息
    void sendMessage(QString envolpe, QString content);
    void sendMessage(Message *msg);
    void stop();
    int startWork();
    //与服务器握手
    void shakeHand();

protected slots:
    void doGetMessage(QString msg);
    void doGetZmqMessage(Message *msg);
    int init();
    void work(){

    }

private:
    BaseClient*client;
};

#endif // ZMQMANAGER_H
