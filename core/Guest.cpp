#include "Guest.h"
#include <cmath>
#include <cctype>
#include <QString>
#include <ctime>

int Guest::getID(){return ID;}

std::string Guest::getPassword(){return Password;}

std::string Guest::getUsername(){return Username;}

std::vector<Book*> Guest::findBook(std::string type, std::string value) {
    std::vector<Book*> books = bm->findBook(QString::fromStdString(type),QString::fromStdString(value));
    return books;
}

int Guest::getbBook(){
    return bBook;
}

int Guest::getoBook(){
    return obook;
}


void Guest::decreaseobook(){
    --obook;
     gm->modifyInfo(this, "obook", QString::number(obook));
}

void Guest::increaseobook(){
    ++obook;
    gm->modifyInfo(this, "obook", QString::number(obook));
}

void Guest::increaseBbook(){
    ++bBook;
    gm->modifyInfo(this, "bbook", QString::number(bBook));
}

void Guest::decreaseBbook(){
    --bBook;
    gm->modifyInfo(this, "bbook", QString::number(bBook));
}

Book** Guest::getbooks(){
    return books;
}

void Guest::getbook(Book *book){
    books[bBook] = bm->findBook("ID", QString::number( book->getID())).front();
}

void Guest::appointment(Book *book) {
    this->increaseobook();
    bm->modifyInfo(book, "GuestID2", QString::number(this->getID()));
}

Guest::Guest(int id, std::string username, std::string password, int bBook_, Book** books_,int obook_, QSqlDatabase& db, int appbook_):
    User(username, id, password), bBook(bBook_), books(books_),obook(obook_), db(db), appbook(appbook_){
    gm = new GuestMysql(db);
    tmysql = new To_doMysql(db);
    bm = new BookMysql(db);
    rmysql = new RecordMysql(db);
}

int Guest::getappbook(){
    return appbook;
}

void Guest::modiappbook(){
    --appbook;
    gm->modifyInfo(this, "appbook", "0");
}

void Guest::modifypassword(QString pw){
    gm->modifyInfo(this, "Password", pw);
}

bool Guest::existUsername(QString username_){
    return gm->existUsername(username_);
}

void Guest::modifyUsername(QString un){
    gm->modifyInfo(this, "Username", un);
}

void Guest::Applyforbook(Book *book) {
    Record* _record  = new Record(this, book, 0);
    tmysql->addRecord(_record);
    _record->modiID(tmysql->get_lastID());
    return;
}

void Guest::ApplyreturnBook(Book *book) {
    tmysql->addRecord(new Record(this, book, 1));
}

int Guest::getType(){return 0;}


std::vector<Record*> Guest::findRecord(QString type, QString value){
    std::vector<Record*> records;
    records = rmysql->findRecord("guest", type, value, QString::number(this->getID()));
    return records;
}

void Guest::exchangeBookID(int n){
    books[n] = books[n+1];
}
