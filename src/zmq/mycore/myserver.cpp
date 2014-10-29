#include "myserver.h"


MyServer::MyServer(QString pubAddr, QString serverAddr, QString identity)
{
    this->publisherBindAddr=pubAddr;
    this->serverBindAddr=serverAddr;
    this->identity=identity;
}

int MyServer::init()
{
    context = zmq_init(1);

    server = zmq_socket(context, ZMQ_REP);

    //    if(this->identity!=NULL){
    //        char*idc=this->identity.toAscii().data();
    //        zmq_setsockopt(server, ZMQ_IDENTITY,idc,strlen(idc));
    //    }

    int rc1=zmq_bind(server,serverBindAddr.toAscii().data());


    publisher = zmq_socket(context, ZMQ_PUB);

    int rc2=zmq_bind(publisher, publisherBindAddr.toAscii().data());

    return (rc1!=-1&&rc2!=-1)?1:-1;

}



void MyServer::work()
{

    this->isWork=true;

    while(1){

        if(!isWork){
            break;
        }

        char*msgEnvolope=ZmqHelper::s_recv(server);

        char*reqContext=ZmqHelper::s_recv(server);

        qDebug("server recive:%s:%s\n",msgEnvolope,reqContext);

        //处理收到的消息，并进行回复
        //在此类内部，doMessage 是一个虚函数，具体实现留给了子类
        char*rsp=this->doMessage(msgEnvolope,reqContext);

        ZmqHelper::s_send(server,rsp);

        free(msgEnvolope);
        free(reqContext);
        //free(rsp);


    }

}



void MyServer::stopWork()
{
    MyAbstractZmq::stopWork();
    zmq_close(server);
    zmq_close(publisher);
    zmq_term(context);

}


void MyServer::publishMessage(QString filter, QString msg)
{
    ZmqHelper::s_sendmore(this->publisher,filter.toAscii().data());
    ZmqHelper::s_send(this->publisher,msg.toAscii().data());
}
