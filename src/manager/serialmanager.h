#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H


#include "basemanager.h"

#include <QObject>


class Serial;

/**
 * 串口通信管理类 管理串口的打开/关闭以及 数据收发
 * @brief The SerialManager class
 */
class SerialManager : public BaseManager
{
    Q_OBJECT
public:
    explicit SerialManager();

signals:
public slots:
    void sendMessage(QString msg);

    void stop();
    int startWork();
protected slots:
    void doGetMessage(QString msg);
    int init();
    void work();
private:
    Serial*serial;
};

#endif // SERIALMANAGER_H
