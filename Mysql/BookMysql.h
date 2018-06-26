#pragma once

#include "Mysql.h"
#include "core/Book.h"
#include "GuestMysql.h"

class Book;
class GuestMysql;
class BookMysql : public Mysql{
    GuestMysql* gm;
    QSqlDatabase &db;
public:
    BookMysql(QSqlDatabase& db);
    std::vector<Book*> findBook(QString type, QString value);
    void modifyInfo(Book* book,QString column,QString info);
    void insertBook(Book* book);
    void dropBook(Book* book);
    void putBookBack(Book* book);
};
