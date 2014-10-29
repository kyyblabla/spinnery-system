#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widget/common_widget.h"


#include <QMainWindow>



class TcpSocketManager;
class SerialManager;
class ZmqManager;
class SqliteManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<QString> getNodeInfoList();

signals:
    void changeStackIndex(int index);

public slots:

private slots:
    void on_pushButton_setting_clicked();

    void on_pushButton_main_clicked();

    void on_pushButton_log_clicked();

    void on_pushButton_topview_clicked();

    void on_pushButton_exit_clicked();

    void doMessage(QString message);

    void on_pushButton_clicked();


    // 处理wifi 下 tcp网络连接的关闭/打开状态
    void doTcpConnected();
    void doTcpDisConnected();

    // 处理串口 关闭/打开状态
    void doSerialOpend();
    void doSerialClosed();

    //处理zmq连接/断开状态
    void doZmqOpen();
    void doZmqClose();


    //处理sql连接/断开状态
    void doSqlOpen();
    void doSqlClose();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    void init();
    void createMenus();
    void createActions();
    void createConnections();


    LogWidget*wLogWidget;
    MainWidget*wMainWidget;
    SystemWidget*wSystemWidget;
    TopeViewWidget*wTopeView;
    ConsoleWidget*wConsole;

    //资源
    //背景图片
    QPixmap main_back_pic;
    QPixmap fengye_pic;

    //socket 通信管理
    TcpSocketManager*tcpSocketManager;

    //串口通信管理
    SerialManager*serialManager;

    //Zmq 通信管理
    ZmqManager*zmqManager;

    //sqllite 数据存储管理
    SqliteManager*sqliteManager;
};

#endif // MAINWINDOW_H
