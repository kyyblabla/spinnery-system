#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QtNetwork>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QString addr,int port);

    //设置/获取端口于地址
    QString getAddr() const;
    void setAddr(const QString &value);

    int getPort() const;
    void setPort(int value);

signals:
    //获取消息
    void getMessage(QString msg);
    //连接成功
    void connected();

    //已经关闭连接
    void disConnected();

public slots:
    //发送消息
    void sendMessage(QString msg);

    //连接
    void connectServer();
    //关闭连接
    void closeConnect();
private slots:

    //接受消息
    void doReadMsg();
    //处理错误消息
    void doError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket* m_socket;
    QString addr; //主机地址
    int port;  //主机端口
};

#endif // TCPCLIENT_H
