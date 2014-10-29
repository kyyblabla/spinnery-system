#ifndef BASECLIENT_H
#define BASECLIENT_H

#include <QObject>




#include "../mycore/myclient.h"



class BaseClient : public MyClient
{
    Q_OBJECT
public:
    explicit BaseClient(QString pubAddr,QString serverAddr, QString subFilter="");
    QString requestServer(Message*msg);

signals:
    void message(Message*msg);

protected:
    char*doMessage(char *envolpe, char *context);

private:



};

#endif // BASECLIENT_H
