#include "config.h"

#include <QSettings>
#include <QTextCodec>

Config::Config(QObject *parent) :
    QObject(parent)
{
}

void Config::init()
{
    QSettings settings("config.ini", QSettings::IniFormat);

    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    this->zId=settings.value("zId","0001").toString();
    this->zMainPubAddress=settings.value("zMainPubAddress","tcp://192.168.1.101:8519").toString();
    this->zMainSevAddress=settings.value("zMainSevAddress","tcp://192.168.1.101:8520").toString();

    this->zServerId=settings.value("zServerId","s8521").toString();

    //串口配置信息
    this->sPortName=settings.value("sPortName","/dev/ttyS0").toString();
    this->sBound=settings.value("sBound","9600").toString().toInt();
    this->sDateBit=settings.value("sDateBit","8").toString().toInt();
    this->sStopBit=settings.value("sStopBit","1").toString().toInt();
    this->sParity=settings.value("sParity","0").toString().toInt();



    //wifi 通信配置信息
    this->tSocketAddr=settings.value("tSocketAddr","127.0.0.1").toString(); //服务器地址
    this->tSocketPort=settings.value("tSocketPort","10000").toString().toInt();




}

void Config::save()
{

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

    settings.setValue("zId",zId);
    settings.setValue("zMainPubAddress",zMainPubAddress);
    settings.setValue("zMainSevAddress",zMainSevAddress);
    settings.setValue("zServerId",zServerId);

    settings.setValue("sPortName",sPortName);
    settings.setValue("sBound",sBound);
    settings.setValue("sDateBit",sDateBit);
    settings.setValue("sStopBit",sStopBit);
    settings.setValue("sParity",sParity);

    settings.setValue("tSocketAddr",tSocketAddr);
    settings.setValue("tSocketPort",tSocketPort);

}
