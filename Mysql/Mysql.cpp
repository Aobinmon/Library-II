#include "Mysql.h"

Mysql::Mysql(QSqlDatabase &db){
    query = new QSqlQuery(db);
}
