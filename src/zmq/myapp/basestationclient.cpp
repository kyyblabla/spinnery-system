#include "basestationclient.h"


BaseStationClient::BaseStationClient(QString pubAddr, QString serverAddr, QString subFilter):MyClient(pubAddr,serverAddr,subFilter)
{

}

char *BaseStationClient::doMessage(char *envolpe, char *context)
{

    if(envolpe==NULL||subFilter.compare(QString(envolpe))!=0){

        return MY_MSG_ERR;

    }

    QString strCon(context);

    qDebug()<<"context"<<strCon;

    Message*msg=new Message(strCon);

    QString code=msg->getValue("code");

    QString from=msg->getValue("from");


    this->getMessage(from+":"+code);

    return MY_MSG_OK;

}

QString BaseStationClient::requestServer(Message *msg)
{
     return MyClient::requestServer(msg->getContent(),msg->getMsgEnvolpe());
}
