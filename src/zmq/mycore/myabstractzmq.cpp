#include "myabstractzmq.h"

MyAbstractZmq::MyAbstractZmq(QObject *parent) :
    QObject(parent),isWork(false),retryTimes(3),replyTimeOut(5000)
{
}

int MyAbstractZmq::startWork()
{

    int rc=this->init();
    if(rc<0){
        return rc;
    }

    QThread*t=new QThread;
    this->moveToThread(t);
    connect(t,SIGNAL(started()),this,SLOT(work()));
    connect(this,SIGNAL(tryStopWork()),t,SLOT(quit()));

    t->start();

    return 1;

}

void MyAbstractZmq::stopWork()
{
    this->isWork=false;
    emit this->tryStopWork();

}
