#include "systemwidget.h"
#include "ui_systemwidget.h"
#include "src/config/config.h"

extern Config*mainSystemConfig; //系统配置指针

SystemWidget::SystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemWidget)
{
    ui->setupUi(this);
}

SystemWidget::~SystemWidget()
{
    delete ui;
}

void SystemWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    //关于串口的设置
    int re=ui->comboBox->findText(mainSystemConfig->sPortName);
    if(re!=-1){
        ui->comboBox->setCurrentIndex(re);
    }else{

        ui->comboBox->addItem(mainSystemConfig->sPortName);
        ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    }


    re=ui->comboBox_bound->findText(QString::number(mainSystemConfig->sBound));
    if(re!=-1){
        ui->comboBox_bound->setCurrentIndex(re);
    }else{

        ui->comboBox_bound->addItem(QString::number(mainSystemConfig->sBound));
        ui->comboBox_bound->setCurrentIndex(ui->comboBox_bound->count()-1);
    }

    re=ui->comboBox_databit->findText(QString::number(mainSystemConfig->sDateBit));
    if(re!=-1){
        ui->comboBox_databit->setCurrentIndex(re);
    }else{

        ui->comboBox_databit->addItem(QString::number(mainSystemConfig->sDateBit));
        ui->comboBox_databit->setCurrentIndex(ui->comboBox_databit->count()-1);
    }

    int intp=mainSystemConfig->sParity>=0&&mainSystemConfig->sParity<3?mainSystemConfig->sParity:0;
    ui->comboBox_parity->setCurrentIndex(intp);



    re=ui->comboBox_stopbit->findText(QString::number(mainSystemConfig->sStopBit));
    if(re!=-1){
        ui->comboBox_stopbit->setCurrentIndex(re);
    }else{

        ui->comboBox_stopbit->addItem(QString::number(mainSystemConfig->sStopBit));
        ui->comboBox_stopbit->setCurrentIndex(ui->comboBox_stopbit->count()-1);
    }


    //zmq 通信设置
    ui->lineEdit_id->setText(mainSystemConfig->zId);
    ui->lineEdit_pubaddr->setText(mainSystemConfig->zMainPubAddress);
    ui->lineEdit_reqaddr->setText(mainSystemConfig->zMainSevAddress);

    //wifi 通信设置
    ui->lineEdit_link_addr->setText(mainSystemConfig->tSocketAddr);
    ui->lineEdit_link_port->setText(QString::number(mainSystemConfig->tSocketPort));


}

void SystemWidget::on_pushButton_2_clicked()
{
    mainSystemConfig->save();
}
