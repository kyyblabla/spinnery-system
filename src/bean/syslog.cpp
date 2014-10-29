#include "syslog.h"

#define SYSLOG_DATE_FORMAT "yyyy-MM-dd hh:mm:ss"

SysLog::SysLog()
{
}


QString SysLog::getInfo() const
{
    return info;
}

void SysLog::setInfo(const QString &value)
{
    info = value;
}
int SysLog::getId() const
{
    return id;
}

void SysLog::setId(int value)
{
    id = value;
}


QDateTime SysLog::getTime() const
{
    return time;
}

QString SysLog::getTimeStr()
{
    return this->time.toString(SYSLOG_DATE_FORMAT);
}

void SysLog::setTime(const QDateTime &value)
{
    time = value;
}

void SysLog::setTimeStr(const QString &value)
{
     time=QDateTime::fromString(value);
}
int SysLog::getType() const
{
    return type;
}

void SysLog::setType(int value)
{
    type = value;
}




