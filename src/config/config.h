#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0);

    void init();

    //关于zeromq的配置
    QString zMainPubAddress; //服务器 pub 地址
    QString zMainSevAddress;   //服务器 req地址
    QString zId; //id 惟一的值，需要指定

    //中间代理服务器地址
    QString zServerId;

    //请求服务器超时时间
    int zTimeout;

    //超时后的重试次数
    int zTimeoutRetryTimes;

    //关于串口的配置
    QString sPortName; //串口名称
    int sBound;  //波特率
    int sDateBit;   //停止位
    int sStopBit;   //停止位
    int sParity;//基偶校验 0 无 1基 2 偶数


    //sqllite

    //tope view


    //tcp sockrt
    QString tSocketAddr; //服务器地址
    int tSocketPort;  //端口

    void save();
signals:

public slots:

};

#endif // CONFIG_H
