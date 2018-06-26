#ifndef LIBRAR_GUEST_H
#define LIBRAR_GUEST_H


#include "User.h"
#include "Book.h"
#include "Mysql/GuestMysql.h"
#include "Mysql/BookMysql.h"
#include "Mysql/To_domysql.h"
#include "Mysql/RecordMysql.h"

class Record;
class Book;
class GuestMysql;
class BookMysql;
class RecordMysql;
class To_doMysql;
class Guest : public User{
    int bBook;
    int obook;
    int appbook;                       //1--预约的书已成功通过借阅申请
    Book** books;
    BookMysql* bm;
    GuestMysql* gm;
    To_doMysql* tmysql;
    RecordMysql* rmysql;
    QSqlDatabase& db;
public:
    Guest(int id, std::string username, std::string password, int bBook, Book** books_,int obook_, QSqlDatabase& db, int appbook=0);
    int getID();
    std::string getUsername();
    std::string getPassword();
    int getbBook();
    std::vector<Record*> findRecord(QString type, QString value);
    std::vector<Book*> findBook(std::string type, std::string value);
    void Applyforbook(Book* book);//申请借书
    void ApplyreturnBook(Book* book);//申请还书
    void appointment(Book* book);//收藏书
    void modifypassword(QString pw);
    int getType();                       //return 0
    void increaseBbook();
    Book** getbooks();
    void decreaseBbook();
    void exchangeBookID(int n);
    void getbook(Book* book);
    void returnBook(Book* book);
    void increaseobook();
    void decreaseobook();
    int getoBook();
    int getappbook();
    void modiappbook();
    bool existUsername(QString username_);
    void modifyUsername(QString un);
};





#endif
