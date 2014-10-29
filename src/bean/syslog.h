#ifndef SYSLOG_H
#define SYSLOG_H

#include <QString>

#include <QDateTime>

class SysLog
{
public:
    SysLog();
    //日志内容
    QString getInfo() const;
    void setInfo(const QString &value);

    int getId() const;
    void setId(int value);

    QDateTime getTime() const;
    QString getTimeStr();
    void setTime(const QDateTime &value);
    void setTimeStr(const QString &value);

    int getType() const;
    void setType(int value);

private:

    QString info;

    //id
    int id;

    //时间戳
    QDateTime time;

    //日志类型
    int type;
};

#endif // SYSLOG_H
