#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "rewidget/mymenulabel.h"
#include "form/exitdialog.h"

#include "src/manager/managers.h"

#include <QDebug>
#include <QPixmap>
#include <QPainter>

#define DEFAULT_F_PIC_WIDTH 80

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    createMenus();
    createActions();
    createConnections();



}

MainWindow::~MainWindow()
{
    delete ui;
    //delete mainManager;
}

QList<QString> MainWindow::getNodeInfoList()
{
    return this->wTopeView->getNodeList();
}


void MainWindow::init()
{
    this->wLogWidget=new LogWidget;

    this->wMainWidget=new MainWidget;

    this->wSystemWidget=new SystemWidget;

    this->wTopeView=new TopeViewWidget;

    this->wConsole=new ConsoleWidget;

    ui->page_main->layout()->addWidget(wMainWidget);
    connect(wMainWidget,SIGNAL(settingButtonClick()),this,SLOT(on_pushButton_setting_clicked()));


    ui->page_log->layout()->addWidget(wLogWidget);
    ui->page_system_setting->layout()->addWidget(wSystemWidget);
    ui->page_topeview->layout()->addWidget(wTopeView);
    ui->page_console->layout()->addWidget(wConsole);

    QString style="border-bottom:2px solid #ccc";

    ui->widget_3->setStyleSheet(style);
    ui->widget_4->setStyleSheet(style);
    ui->widget_5->setStyleSheet(style);
    ui->widget->setStyleSheet(style);


    //窗口样式修改
    // setWindowFlags(Qt::FramelessWindowHint);
    //this->showFullScreen();

    //载入资源图片
    main_back_pic.load(":/mainrs/main_back.png");
    fengye_pic.load(":/mainrs/icon_f1.png");

    //tcp 网络链接管理 主要用在通过wifi控制小车
    tcpSocketManager=new TcpSocketManager;

    connect(tcpSocketManager,SIGNAL(connected()),this,SLOT(doTcpConnected()));
    connect(tcpSocketManager,SIGNAL(destroyed()),this,SLOT(doTcpDisConnected()));
    connect(this->wMainWidget,SIGNAL(tryWifiLinkAgin()),tcpSocketManager,SLOT(startWork()));

    tcpSocketManager->startWork();


    //串口通信管理 主要用于与无线协调器通信
    serialManager=new SerialManager;
    connect(serialManager,SIGNAL(connected()),this,SLOT(doSerialOpend()));
    connect(serialManager,SIGNAL(disConnected()),this,SLOT(doSerialClosed()));
    connect(this->wMainWidget,SIGNAL(trySerialOpenAgin()),serialManager,SLOT(startWork()));

    serialManager->startWork();


    //zmq 通信管理，主要是与上位机之间的通信
    zmqManager=new ZmqManager;
    connect(zmqManager,SIGNAL(connected()),this,SLOT(doZmqOpen()));
    connect(zmqManager,SIGNAL(disConnected()),this,SLOT(doZmqClose()));
    connect(wMainWidget,SIGNAL(tryZmqOpenAgin()),zmqManager,SLOT(startWork()));

    zmqManager->startWork();
    //this->statusBar()->showMessage("ssssssss",10000);


    sqliteManager=new SqliteManager;
    connect(sqliteManager,SIGNAL(connected()),this,SLOT(doSqlOpen()));
    connect(sqliteManager,SIGNAL(disConnected()),this,SLOT(doSqlClose()));
    connect(wMainWidget,SIGNAL(trySqlOpenAgin()),sqliteManager,SLOT(startWork()));

    sqliteManager->startWork();




}

void MainWindow::createMenus()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createConnections()
{
    connect(this,SIGNAL(changeStackIndex(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    connect(wConsole,SIGNAL(senMessage(QString,QString)), zmqManager,SLOT(sendMessage(QString,QString)));

    connect(zmqManager,SIGNAL(getMessage(QString)),wConsole,SLOT(getMessage(QString)));

}


void MainWindow::on_pushButton_main_clicked()
{
    emit changeStackIndex(0);
}

void MainWindow::on_pushButton_log_clicked()
{
    emit changeStackIndex(1);
}

void MainWindow::on_pushButton_topview_clicked()
{
    emit changeStackIndex(2);
}


void MainWindow::on_pushButton_setting_clicked()
{
    emit changeStackIndex(3);
}


void MainWindow::on_pushButton_exit_clicked()
{
    ExitDialog d(this);

    //退出系统
    if(d.exec()){
        qApp->quit();
    }

}

void MainWindow::doMessage(QString message)
{
    qDebug()<<"main recv:"+message;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    //绘制背景
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),main_back_pic,0,0,this->width(),this->height());

    //绘制两片枫叶
    int x=this->width()-DEFAULT_F_PIC_WIDTH-18;
    int y=9;

    p.drawPixmap(x,y,DEFAULT_F_PIC_WIDTH,DEFAULT_F_PIC_WIDTH,this->fengye_pic,0,0,this->fengye_pic.width(),this->fengye_pic.height());

    x=this->width()-DEFAULT_F_PIC_WIDTH*2-18;

    p.drawPixmap(x,y,DEFAULT_F_PIC_WIDTH,DEFAULT_F_PIC_WIDTH,this->fengye_pic,0,DEFAULT_F_PIC_WIDTH/2-15,this->fengye_pic.width(),this->fengye_pic.height());


}

void MainWindow::on_pushButton_clicked()
{
    emit changeStackIndex(4);
}

void MainWindow::doTcpConnected()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevWiFi,BASE_STATION_DEV_STATU_NORMAL);
}

void MainWindow::doTcpDisConnected()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevWiFi,BASE_STATION_DEV_STATU_ERR);
}

void MainWindow::doSerialOpend()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevSerial,BASE_STATION_DEV_STATU_NORMAL);
}

void MainWindow::doSerialClosed()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevSerial,BASE_STATION_DEV_STATU_ERR);
}


void MainWindow::doZmqOpen()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevEth4Zmq,BASE_STATION_DEV_STATU_NORMAL);

}

void MainWindow::doZmqClose()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevEth4Zmq,BASE_STATION_DEV_STATU_ERR);
}

void MainWindow::doSqlOpen()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevSqlite,BASE_STATION_DEV_STATU_NORMAL);
}

void MainWindow::doSqlClose()
{
    this->wMainWidget->updateDeviceStatus(MainWidget::DevSqlite,BASE_STATION_DEV_STATU_ERR);
}

