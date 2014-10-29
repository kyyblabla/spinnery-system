#ifndef MYSERVER_H
#define MYSERVER_H

#include "myabstractzmq.h"

#include <QObject>

class MyServer : public MyAbstractZmq
{
    Q_OBJECT
public:
    //explicit MyServer(QObject *parent = 0);
    MyServer(QString pubAddr,QString serverAddr,QString identity);
signals:

protected slots:
    int init();
    void work();
public slots:
    //int startWork();
    void stopWork();

    void publishMessage(QString filter,QString msg);

protected:
    //用于内容发布
    void*publisher;
    QString publisherBindAddr;

    //用于请求应答
    void*server;
    QString serverBindAddr;

    QString identity;
};

#endif // MYSERVER_H
