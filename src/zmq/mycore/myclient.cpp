#include "myclient.h"

MyClient::MyClient(QString pubAddr, QString serverAddr, QString subFilter)
{
    this->pubAddr=pubAddr;
    this->serverAddr=serverAddr;
    this->subFilter=subFilter;
}

void MyClient::setSubFilter(QString filter)
{
    this->subFilter=filter;
}

int MyClient::init()
{

    context = zmq_init(1);

    this->client = zmq_socket(context, ZMQ_REQ);
    int rc1=zmq_connect(client,this->serverAddr.toAscii().data());

    this->suber = zmq_socket(context, ZMQ_SUB);
    int rc2=zmq_connect(suber,this->pubAddr.toAscii().data());
    char*filter=this->subFilter.toAscii().data();
    zmq_setsockopt(suber,ZMQ_SUBSCRIBE,filter,strlen(filter));

    return (rc1!=-1&&rc2!=-1)?1:-1;

}

void MyClient::work()
{


    this->isWork=true;
    qDebug()<<"clent start!";

    while(1){

        if(isWork==false){
            break;
        }

        //信封
        char*envolope=ZmqHelper::s_recv(suber);

        //正文，是以xml格式表示的字符串
        char*context=ZmqHelper::s_recv(suber);

        qDebug("client recive:\n%s:\n%s\n----------------\n",envolope,context);

        //处理数据，这里并没有处理，而是交给子类来实现
        this->doMessage(envolope,context);

        free(envolope);
        free(context);

    }


}

void MyClient::stopWork()
{

    MyAbstractZmq::stopWork();
    zmq_close(suber);
    zmq_close(client);
    zmq_term(context);

}

QString MyClient::requestServer(QString req, bool enableTimeout)
{

    int rc=ZmqHelper::s_send(client,req.toAscii().data());

    if(rc!=-1){

        char*rsp;
        if(!enableTimeout){
            rsp=ZmqHelper::s_recv(client);
        }else{
            rsp=ZmqHelper::s_recv(client,this->replyTimeOut,this->retryTimes);
        }

        QString rspStr(rsp);
        free(rsp);
        return rspStr;

    }

    return NULL;
}

QString MyClient::requestServer(QString req, QString identify, bool enableTimeout)
{
    ZmqHelper::s_sendmore(client,identify.toAscii().data());

    ZmqHelper::s_send(client,req.toAscii().data());

    char*rsp;
    if(!enableTimeout){

        rsp=ZmqHelper::s_recv(client);

    }else{

        rsp=ZmqHelper::s_recv(client,this->replyTimeOut,this->retryTimes);
    }

    QString rspStr(rsp);

    free(rsp);

    return rspStr;
}
