#ifndef MESSAGE_H
#define MESSAGE_H


#include "messageuitl.h"

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:

    Message(QString msgEnvolope,QString msgContext="");

    ~Message();

    QString getMsgEnvolpe();

    bool isLegialMwssage();

    QString msgEnvolope;

    QString getContent();

    QString getValue(QString key, QString attrName="");

    QList<QString> getValues(QString pkey, QString ckey, QString attrName="");

    int setValues(QString ptagName,  QString ctagName,QList<QString> values,QString attrName="");


    int setValue(QString key, QString value,QString attrName="");
private:
    QDomDocument*context;
};

#endif // MESSAGE_H
