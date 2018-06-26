#ifndef LIBRAR_ADIMINISTRATOR_H
#define LIBRAR_ADIMINISTRATOR_H

#include <QString>
#include <string>
#include "Guest.h"
#include <vector>
#include "Mysql/To_domysql.h"
#include "Mysql/BookMysql.h"
#include "Mysql/GuestMysql.h"
#include "Mysql/RecordMysql.h"
#include "Mysql/AdministratorMysql.h"
class GuestMysql;
class BookMysql;
class RecordMysql;
class To_doMysql;
class AdministratorMysql;
class Administrator : public User{
    QSqlDatabase& db;
    GuestMysql* gm;
    BookMysql *bm;
    RecordMysql *rm;
    To_doMysql *tm;
    AdministratorMysql* am;
public:
    Administrator(int id, std::string _username, std::string _password, QSqlDatabase& db);
    int approve_or_refuse(Record* record,int approve);
    std::vector<Book*> findBook(std::string type, std::string value);
    std::vector<Record*> findRecord(QString type, QString value); //type包括时间，序号，书名
    std::vector<Guest*> find_guest(std::string type, std::string value);  //type包括用户名，ID
    void addBook(Book* book);//书库中加书
    void deleteBook(Book* book);//书库中减书
    bool returnBook(Record* record);
    void modifyBook(Book* book, QString column, QString value);
    void deleteGuest(Guest* guest);
    void modifyGuest(Guest* guest, QString column, QString value);
    int getType();           //return 1
    int getID();
    std::string getUsername();
    std::string getPassword();
    void modifypassword(QString pw);
    QSqlDatabase& getdb();
};



#endif
