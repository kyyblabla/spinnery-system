#include "serialmanager.h"

#include "src/config/config.h"
#include "src/serial/serial.h"


#include <QThread>

extern Config*mainSystemConfig;

SerialManager::SerialManager()
{

    this->serial=new Serial;

    connect(serial,SIGNAL(message(QString)),this,SIGNAL(getMessage(QString)));


}

void SerialManager::sendMessage(QString msg)
{
    serial->sendMesg(msg);
}

void SerialManager::doGetMessage(QString msg)
{
    qDebug()<<"serial recv:"<<msg;
}

void SerialManager::stop()
{
    serial->close();
}

int SerialManager::startWork()
{

    int rc=this->init();
    if(rc<0){
        emit this->disConnected();
        return rc;
    }

    emit this->connected();

    QThread*t=new QThread;
    this->moveToThread(t);
    connect(t,SIGNAL(started()),this,SLOT(work()));
    t->start();

    return 1;

}

int SerialManager::init()
{

    SerialConfig*config=new SerialConfig;

    config->serialPort=mainSystemConfig->sPortName.toAscii().data();

    config->baudRate=mainSystemConfig->sBound;
    config->characterSize=mainSystemConfig->sDateBit;
    config->parity=mainSystemConfig->sParity;
    config->stopBits=mainSystemConfig->sStopBit;

    bool b=this->serial->open(config);

    return b?1:-1;

}

void SerialManager::work()
{
    this->serial->work();

}
