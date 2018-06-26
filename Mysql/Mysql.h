#ifndef MYSQL_H
#define MYSQL_H
#include <QtSql/QtSql>
#include <QString>
class Mysql{
public:
    QSqlQuery* query;
    Mysql(QSqlDatabase& db);
    virtual ~Mysql(){}
};

#endif
