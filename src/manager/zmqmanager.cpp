#include "zmqmanager.h"

#include "src/config/config.h"
#include "src/zmq/myapp/baseclient.h"


extern Config*mainSystemConfig;

ZmqManager::ZmqManager()
{
    this->client=NULL;
}

void ZmqManager::sendMessage(QString content)
{
    sendMessage(mainSystemConfig->zServerId,content);
}

void ZmqManager::sendMessage(QString envolpe, QString content)
{
    Message*msg=new Message(envolpe,content);
    sendMessage(msg);
}

void ZmqManager::sendMessage(Message *msg)
{

    QString re=this->client->requestServer(msg);

    emit this->getMessage(tr("server replay:")+re);


}


void ZmqManager::stop()
{
    client->stopWork();
}

int ZmqManager::startWork()
{

    this->init();

    int rc=this->client->startWork();

    if(rc==1){
        qDebug()<<"zmq:try to shake hand!";
        shakeHand();
    }else{
        qDebug()<<"zmq:cannot start zmq!";
        emit this->disConnected();
    }

    return rc;
}

void ZmqManager::shakeHand()
{
    Message*msg=new Message(mainSystemConfig->zServerId);

    msg->setValue("type","s1");

    QString re=this->client->requestServer(msg);

    doGetMessage(re);

}

void ZmqManager::doGetMessage(QString msg)
{
    Message*repMsg=new Message(NULL,msg);

    doGetZmqMessage(repMsg);
}


//处理接收到的消息
void ZmqManager::doGetZmqMessage(Message *msg)
{
    QString type=msg->getValue("type");
    QString from=msg->getValue("from");

    //获取基站运行状态，直接回复
    if(type.compare(BASE_STATION_CONN_STATUS)==0){


        emit this->getMessage(from+tr(" request for status"));

        //回应
        Message*repMsg=new Message(from,NULL);

        repMsg->setValue("type",BASE_STATION_CONN_STATUS);
        repMsg->setValue("from",mainSystemConfig->zId);
        repMsg->setValue("addr",from);
        repMsg->setValue("data",MY_MSG_OK);

        this->sendMessage(repMsg);

    }
    //来自于服务器的状态命令
    if(type.compare(CENTER_SERVER_STATION_CONN_STATUS)==0){



        QString status=msg->getValue("status");

        emit this->getMessage(tr("get server status:")+status);

        //服务器运行状态正常
        if(status.compare(MY_MSG_OK)==0){
            emit this->connected();
        }else{
            emit this->disConnected();
        }

    }
    //获取到小车的控制命令
    else if(type.compare(BASE_STATION_CONN_CAR)==0){

        QString command=msg->getValue("command");

        emit this->getMessage(tr("get car command:")+command);


    }
    //获取到请求拓扑连接状态的命令
    else  if(type.compare(BASE_STATION_CONN_TOPE)==0){



    }
    //获取传感器状态的命令
    else if(type.compare(BASE_STATION_CONN_SENIOR)==0){



    }

}

int ZmqManager::init()
{
    this->client=new BaseClient(mainSystemConfig->zMainPubAddress,mainSystemConfig->zMainSevAddress,mainSystemConfig->zId);
    connect(client,SIGNAL(message(Message*)),this,SLOT(doGetZmqMessage(Message*)));

}


