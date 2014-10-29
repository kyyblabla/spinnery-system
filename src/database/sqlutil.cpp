#include "sqlutil.h"

SqlUtil::SqlUtil(QObject *parent) :
    QObject(parent)
{
}

bool SqlUtil::createConnection()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("spinnery_system");


    if (!db.open())
    {
        return false;
    }

    QSqlQuery q;

    if (q.exec("CREATE TABLE IF NOT EXISTS system_info(id INTEGER PRIMARY KEY AUTOINCREMENT,messgae VARCHAR(100),createTime timestamp)") == false)
    {
        qDebug()  << "cannot create table system_info" << endl;
        return false;
    }

    return true;


}
