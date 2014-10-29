#include "message.h"


Message::Message(QString msgEnvolope, QString msgContext)
{
    this->msgEnvolope=msgEnvolope;
    context=MessageUitl::parse(msgContext);


}

Message::~Message()
{
    delete context;
}

QString Message::getMsgEnvolpe()
{
    return this->msgEnvolope;
}

bool Message::isLegialMwssage()
{
    return this->context!=NULL;
}

QString Message::getContent()
{
    return MessageUitl::conetxt(context);
}

QString Message::getValue(QString key, QString attrName)
{
    return MessageUitl::getStrByTagName(this->context,key,attrName);
}

QList<QString> Message::getValues(QString pkey, QString ckey, QString attrName)
{
    return  MessageUitl::getStrByTagName(context,pkey,ckey,attrName);
}

int Message::setValues(QString ptagName, QString ctagName, QList<QString> values, QString attrName)
{
    return  MessageUitl::addValues(context,ptagName,ctagName,attrName,values);
}

int Message::setValue(QString key, QString value, QString attrName)
{
    return MessageUitl::addValue(context,key,attrName,value);
}






