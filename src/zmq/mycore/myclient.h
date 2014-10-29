#ifndef MYCLIENT_H
#define MYCLIENT_H

#include "myabstractzmq.h"

#include <QObject>


/**
  客户端抽象对象，实现了基本的通信功能，预留出了 doMessage 接口，由资子类实现进行通信数据的逻辑处理
 * @brief The MyClient class
 */
class MyClient : public MyAbstractZmq
{
    Q_OBJECT
public:
    MyClient(QString pubAddr,QString serverAddr, QString subFilter="");

    //设置订阅
    void setSubFilter(QString filter);
signals:

protected:
    //订阅号，可用来作为本机id标识
    QString subFilter;
    //用来接收服务器的广播消息 进行 sub／pub 通信
    void*suber;

    //服务器广播地址
    QString pubAddr;

    //用来进行 req／rep 通信
    void*client;
    QString serverAddr;

protected slots:
    int init();
    void work();
public slots:
    //int startWork();
    void stopWork();

    /**
     * @brief requestServer 向服务器发出请求
     * @param req
     * @return
     */
    QString requestServer(QString req,bool enableTimeout=false);

    /**
     * @brief requestServer  向服务器发出有目的地址的请求，可认为进行1对1通信
     * @param req
     * @param identify
     * @return
     */
    QString requestServer(QString req,QString identify,bool enableTimeout=false);

};

#endif // MYCLIENT_H
