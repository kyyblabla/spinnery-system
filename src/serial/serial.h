#ifndef SERIAL_H
#define SERIAL_H

#include "common.h"
#include "SerialStream.h"
#include "SerialStreamBuf.h"
#include <QObject>

using namespace std;
using namespace LibSerial;


typedef struct
{
    int baudRate;        //!<波特率
    int characterSize;   //!<传输位
    int stopBits;        //!<停止位
    int parity;          //!校验位 0无校验 1奇校验 2偶校验
    char*serialPort; //!设备文件名

}SerialConfig;


class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = 0);

signals:
    void message(QString msg);
public slots:

    bool open(SerialConfig*config);
    void work();
    void close();
    void sendMesg(QString msg);
private slots:

private:
    void initSerialStream(SerialConfig*config);
    SerialStream serialStream;
    bool isRuning;
};

#endif // SERIAL_H
