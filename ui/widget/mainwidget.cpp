#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDateTime>
#include <QDebug>
#include <QPainter>



MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    QObjectList list= ui->main_widget_seting_list->children();

    foreach (QObject*obj, list) {

        if (QPushButton *button = qobject_cast<QPushButton *>(obj)){

            connect(button,SIGNAL(clicked()),this,SIGNAL(settingButtonClick()));

        }
    }

    connect(ui->pushButton_try_wifi,SIGNAL(clicked()),this,SIGNAL(tryWifiLinkAgin()));
    connect(ui->pushButton_try_serial,SIGNAL(clicked()),this,SIGNAL(trySerialOpenAgin()));
    connect(ui->pushButton_try_eth,SIGNAL(clicked()),this,SIGNAL(tryZmqOpenAgin()));
    connect(ui->pushButton_try_sqlite,SIGNAL(clicked()),this,SIGNAL(trySqlOpenAgin()));

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::doMessage(QString msg)
{

    QDateTime time = QDateTime::currentDateTime();

    QString str = time.toString("yyyy-MM-dd hh:mm:ss");

    ui->plainTextEdit->appendHtml("["+str+"]"+msg);


}

void MainWidget::updateDeviceStatus(MainWidget::BaseStationDev dev, int status)
{
    bool enable= (status==BASE_STATION_DEV_STATU_NORMAL)?true:false;

    QString text;

    switch (dev) {
    case DevSerial:
        ui->pushButton_try_serial->setEnabled(!enable);
        text=enable?"<span style=\"color:#000;\">Serial was opend!</span>":"<span style=\"color:#ff0000;\">Serial was not closed!</span>";
        ui->label_serial->setText(text);
        break;
    case DevWiFi:
        ui->pushButton_try_wifi->setEnabled(!enable);
        text=enable?"<span style=\"color:#000;\">Wifi was opend!</span>":"<span style=\"color:#ff0000;\">Wifi was closed!</span>";
        ui->label_wifi->setText(text);
        break;

    case DevSqlite:
        ui->pushButton_try_sqlite->setEnabled(!enable);
        text=enable?"<span style=\"color:#000;\">Sqlite was opend!</span>":"<span style=\"color:#ff0000;\">Sqlite was closed!</span>";
        ui->label_sqlite->setText(text);
        break;
    case DevEth4Zmq:

        ui->pushButton_try_eth->setEnabled(!enable);
        text=enable?"<span style=\"color:#000;\">Eth is working</span>":"<span style=\"color:#ff0000;\">Eth was breakout!</span>";
        ui->label_eth->setText(text);
        break;


    default:
        break;
    }
}
