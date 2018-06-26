#ifndef ADMINISTRATORMYSQL
#define ADMINISTRATORMYSQL

#include "core/Administrator.h"
#include "core/constant.h"


class Administrator;
class AdministratorMysql : public Mysql{
public:
    QSqlDatabase& db;
    AdministratorMysql(QSqlDatabase& db);
    int existUsername(QString username);
    QString getPassword(QString username);
    void modifyPassword(QString password, int ID);
    Administrator* findAd(QString type, QString feature);
};

#endif
