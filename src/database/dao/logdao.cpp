#include "logdao.h"

#include "src/bean/syslog.h"

#include "../sqlutil.h"
#include "../qtsql_common.h"

#include <QSqlQuery>

LogDao::LogDao(QObject *parent) :
    QObject(parent)
{

}

bool LogDao::save(SysLog*sysLog)
{
    QSqlQuery q;

    QString sql="insert into system_info(messgae,createTime) values('"+sysLog->getInfo()+"','"+sysLog->getTimeStr()+"')";

    return q.exec(sql);

}

QList<SysLog*> LogDao::getAll()
{

    QList<SysLog*> list;

    QString sql="select * from system_info";

    QSqlQuery q;

    if(q.exec(sql)){

        while(q.next()){
            SysLog*syslog=new SysLog;

            syslog->setId(q.value(0).toInt());
            syslog->setInfo(q.value(1).toString());
            syslog->setTime(q.value(2).toDateTime());

            list.append(syslog);

        }
    }

    return list;

}

QList<SysLog *> LogDao::getByTime(QDateTime min, QDateTime max)
{
    QList<SysLog*> list;

    return list;
}

SysLog *LogDao::findById(int id)
{

    QString sql="select * from system_info where id="+id;

    QSqlQuery q;

    if(q.exec(sql)){

        SysLog*syslog=new SysLog;

        syslog->setId(q.value(0).toInt());
        syslog->setInfo(q.value(1).toString());
        syslog->setTime(q.value(2).toDateTime());

        return syslog;
    }

    return NULL;

}

bool LogDao::connectSqlite()
{
    return SqlUtil::createConnection();
}
