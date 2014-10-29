#include "sqlitemanager.h"

#include "src/database/dao/logdao.h"


SqliteManager::SqliteManager(QObject *parent) :
    QObject(parent)
{
    logDao=new LogDao;
}

int SqliteManager::startWork()
{
    int rc=init();
    if(rc!=1){

        this->disConnected();

        return rc;
    }


    emit this->connected();

    return 1;

}

QList<SysLog *> SqliteManager::getAll()
{
    return logDao->getAll();
}

bool SqliteManager::save(SysLog *sysLog)
{
    return logDao->save(sysLog);
}

int SqliteManager::init()
{
    bool rc= logDao->connectSqlite();
    return rc?1:-1;

}
