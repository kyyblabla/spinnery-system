#ifndef MYABSTRACTZMQ_H
#define MYABSTRACTZMQ_H

#include "../common.h"

#include <QObject>

/**
  抽象zmq对象，定义了最基本的zmq通信接口
 * @brief The MyAbstractZmq class
 */
class MyAbstractZmq : public QObject
{
    Q_OBJECT
public:
    explicit MyAbstractZmq(QObject *parent = 0);

signals:
    //发布信息
    void getMessage(QString msg);

    //强制停止信号
    void tryStopWork();
protected:
    void *context;
    bool isWork;

    //无法得到服务器响应后的重试次数
    int  retryTimes;

    //等待响应的超时时间
    long replyTimeOut;

protected slots:
    //处理信息
    virtual char* doMessage(char* envolpe,char*context)=0;

    //初始话化
    virtual int init()=0;

    //业余处理
    virtual void work()=0;

public slots:

    //开启业务
    int startWork();

    void stopWork();


};

#endif // MYABSTRACTZMQ_H
