#pragma once

#include "Mysql.h"
#include "core/record.h"
#include "BookMysql.h"
#include "GuestMysql.h"

class Record;
class GuestMysql;

class To_doMysql : public Mysql{
private:
    BookMysql* bm;
    GuestMysql* gm;
public:
    To_doMysql(QSqlDatabase& db);
    void deleteRecord(Record* record);
    void addRecord(Record* record);
    std::vector<Record*> get_all();
    std::vector<Record*> findRecord(QString column, QString value);
    int get_lastID();
};
