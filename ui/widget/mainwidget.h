#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>



#define BASE_STATION_DEV_STATU_NORMAL 1
#define BASE_STATION_DEV_STATU_ERR    0



namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


    //设备代号
    enum BaseStationDev{
        DevSerial=0, //窜口设备
        DevSqlite,   //数据库
        DevWiFi,     //WIFI
        DevEth4Zmq   //以太网卡，用于zeromq通信
    };


signals:
    void settingButtonClick();
    void tryWifiLinkAgin();
    void trySerialOpenAgin();
    void tryZmqOpenAgin();
    void trySqlOpenAgin();
public slots:
    void doMessage(QString msg);
    void updateDeviceStatus(BaseStationDev dev,int status);
protected:

private slots:

private:
    Ui::MainWidget *ui;



};

#endif // MAINWIDGET_H
