#ifndef BASESTATIONCLIENT_H
#define BASESTATIONCLIENT_H

#include "../mycore/myclient.h"


class BaseStationClient : public MyClient
{

public:
    BaseStationClient(QString pubAddr,QString serverAddr, QString subFilter="");
    QString requestServer(Message*msg);
protected:
    char*doMessage(char *envolpe, char *context);



};

#endif // BASESTATIONCLIENT_H
