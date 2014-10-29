#ifndef SQLUTIL_H
#define SQLUTIL_H


#include "qtsql_common.h"
#include <QObject>


class SqlUtil : public QObject
{
    Q_OBJECT
public:
    explicit SqlUtil(QObject *parent = 0);
    static bool createConnection();
signals:

public slots:


};

#endif // SQLUTIL_H
