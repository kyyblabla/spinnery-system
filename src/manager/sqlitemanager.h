#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QObject>

class LogDao;
class SysLog;

class SqliteManager : public QObject
{
    Q_OBJECT
public:
    explicit SqliteManager(QObject *parent = 0);
signals:
    void connected();
    void disConnected();

public slots:
    int startWork();

    QList<SysLog*> getAll();
    bool save(SysLog*sysLog);

private:
    int init();
    LogDao*logDao;

};

#endif // SQLITEMANAGER_H
