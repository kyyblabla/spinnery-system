#include "serial.h"

Serial::Serial(QObject *parent) :
    QObject(parent)
{
}

bool Serial::open(SerialConfig *config){

    serialStream.Open(config->serialPort);

    if(!serialStream.IsOpen())
    {
        qDebug("open serial error\r\n");
        return false;
    }

    initSerialStream(config);

    return true;

}


void Serial::work(){

    //缓存数据
    char *msg = new char[255];
    int index = 0;
    char next_byte ;    //串口接收到的下一个字节
    this->isRuning=true;
    forever{
        //
        if(this->isRuning==false){
            break;
        }

        serialStream.get( next_byte );
        if(next_byte != '#')
        {
            msg[index] = next_byte;
            index++;
            qDebug()<<next_byte;
        }
        else
        {
            msg[index] = '\0';
            index = 0;
            qDebug("%s",msg);
            emit message(QString(msg));

        }
    }
}


void Serial::close(){

    this->isRuning=false;
}

void Serial::sendMesg(QString msg)
{

    char*cmsg =msg.toAscii().data();

    serialStream.write(cmsg,strlen(cmsg));

}


void Serial::initSerialStream(SerialConfig *config)
{

    SerialStreamBuf::BaudRateEnum baudRate;

    switch (config->baudRate) {
    case 9600:
        baudRate=SerialStreamBuf::BAUD_9600;
        break;
    default:
        baudRate=SerialStreamBuf::BAUD_115200;
        break;
    }

    SerialStreamBuf::CharSizeEnum characterSize;
    switch (config->characterSize) {
    case 7:
        characterSize=SerialStreamBuf::CHAR_SIZE_7;
        break;
    default:
        characterSize=SerialStreamBuf::CHAR_SIZE_8;
        break;
    }


    SerialStreamBuf::ParityEnum parity;
    switch (config->characterSize) {
    case 0:
        parity=SerialStreamBuf::PARITY_NONE;
        break;
    case 1:
        parity=SerialStreamBuf::PARITY_ODD;
        break;
    default:
        parity=SerialStreamBuf::PARITY_EVEN;
        break;
    }


    serialStream.SetBaudRate(baudRate);
    serialStream.SetCharSize(characterSize);
    serialStream.SetNumOfStopBits(config->stopBits);
    serialStream.SetParity(parity);
}
