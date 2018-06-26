#include "To_domysql.h"

To_doMysql::To_doMysql(QSqlDatabase& db):Mysql(db){
    gm = new GuestMysql(db);
    bm = new BookMysql(db);
}

int To_doMysql::get_lastID(){
    query->exec("select * from waiting_record");
    int ID;
    while(query->next()){
        ID = query->value(0).toInt();
    }
    return ID;
}

void To_doMysql::addRecord(Record *record){
    query->exec("insert into waiting_record (BookID, GuestID, Type, Time)"
               "VALUES"
               "( " + QString::number(record->getBook()->getID()) + ", "
               + QString::number(record->getGuest()->getID()) + ", "
               + QString::number(record->getType()) + ", "
               +"NOW())");
    qDebug() << record->getBook()->getID();
}

std::vector<Record*> To_doMysql::get_all(){
    std::vector<Record*> records;
    query->exec("select * from waiting_record");
    while(query->next()){
        int id = query->value(0).toInt();
        int Bid = query->value(1).toInt();
        int Gid = query->value(2).toInt();
        int type = query->value(3).toInt();
        std::string time = query->value(4).toString().toStdString();
        Book* book = bm->findBook("ID", QString::number(Bid)).front();
        Guest* guest = gm->find_guest("ID", QString::number(Gid)).front();
        records.push_back(new Record(guest, book, type, id, 2, time));
    }
    return records;
}

std::vector<Record*> To_doMysql::findRecord(QString column, QString value){
    std::vector<Record*> records;
    if(column == "ID" || column == "BookID" || column == "GuestID")
    query->exec("select * from waiting_record where " + column + "=" + value);
    else query->exec("select * from waiting_record where " + column + "=\"" + value + "\"");
    while(query->next()){
        int id = query->value(0).toInt();
        int Bid = query->value(1).toInt();
        int Gid = query->value(2).toInt();
        int type = query->value(3).toInt();
        std::string time = query->value(4).toString().toStdString();
        Book* book = bm->findBook("ID", QString::number(Bid)).front();
        Guest* guest = gm->find_guest("ID", QString::number(Gid)).front();
        records.push_back(new Record(guest, book, type, 2, id, time));
    }
    return records;
}

void To_doMysql::deleteRecord(Record *record){
    query->exec("delete from waiting_record where ID=" + QString::number(record->getID()));
}
