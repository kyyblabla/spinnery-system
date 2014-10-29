#ifndef LOGDAO_H
#define LOGDAO_H

#include <QObject>
#include <QDateTime>

class SysLog;

class LogDao : public QObject
{
    Q_OBJECT
public:
    explicit LogDao(QObject *parent = 0);

signals:

public slots:
    bool save(SysLog *sysLog);
    QList<SysLog*> getAll();
    QList<SysLog*> getByTime(QDateTime min,QDateTime max);
    SysLog*findById(int id);
    bool connectSqlite();
};

#endif // LOGDAO_H
