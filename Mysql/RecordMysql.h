#ifndef RECORDMYSQL_H
#define RECORDMYSQL_H
#include "Mysql.h"
#include "core/Record.h"
#include <vector>
#include <QString>

class Record;
class GuestMysql;
 class RecordMysql : public Mysql{
     BookMysql* bm;
     GuestMysql* gm;
 public:
     RecordMysql(QSqlDatabase& db);
     std::vector<Record*> findRecord( QString usertype,QString infotype, QString info,QString userID);
     void approve_or_refuse(Record* record, int approve);
 };

#endif // RECORDMYSQL_H
