#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QObject>


class QWidget;

/**
 * 通讯管理基类
 * @brief The BaseManager class
 */
class BaseManager : public QObject
{
    Q_OBJECT
public:

    explicit BaseManager();

signals:
    void getMessage(QString msg);
    void connected();
    void disConnected();
public slots:
    virtual void sendMessage(QString msg)=0;
    int startWork();
    void stop() {
    }
protected slots:
    virtual void doGetMessage(QString msg)=0;
    virtual int init()=0;
    virtual void work()=0;

};

#endif // BASEMANAGER_H
