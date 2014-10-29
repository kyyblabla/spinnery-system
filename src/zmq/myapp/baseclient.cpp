#include "baseclient.h"


BaseClient::BaseClient(QString pubAddr, QString serverAddr, QString subFilter) :
    MyClient(pubAddr,serverAddr,subFilter)
{
}

QString BaseClient::requestServer(Message *msg)
{

    return MyClient::requestServer(msg->getContent(),msg->getMsgEnvolpe(),true);

}

char *BaseClient::doMessage(char *envolpe, char *context)
{

    if(envolpe==NULL){
        return MY_MSG_ERR;
    }

    QString strEnvolpe(envolpe);

    if(subFilter.compare(strEnvolpe)==0){

        QString strCon(context);

        Message*msg=new Message(strEnvolpe,strCon);

        emit message(msg);

        return MY_MSG_OK;
    }else{

        return MY_MSG_ERR;

    }

}

