#ifndef GUESTMYSQL_H
 #define GUESTMYSQL_H
 #include "Mysql.h"
 #include <QString>
 #include "core/Guest.h"
#include "BookMysql.h"
class Guest;
class BookMysql;
class GuestMysql:public Mysql{
    BookMysql* bm;
    QSqlDatabase& db;
 public:
     GuestMysql(QSqlDatabase& db);
     void modifyInfo(Guest* guest, QString column, QString value);
     int existUsername(QString username);
     QString getPassword(QString username);
     void dropGuest(Guest* guest);
     void addGuest(QString Username, QString Password);
     std::vector<Guest*> find_guest(QString type, QString feature);
     std::vector<Guest*> browse_guest(QString type, QString feature);         //模糊查找
};

 #endif
