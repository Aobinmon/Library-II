#include "Administrator.h"
#include <QString>
#include <QDebug>

Administrator::Administrator(int id, std::string username, std::string password, QSqlDatabase& db):
    User(username, id, password), db(db){
    rm = new RecordMysql(db);
    tm = new To_doMysql(db);
    bm = new BookMysql(db);
    gm = new GuestMysql(db);
    am = new AdministratorMysql(db);
}

void Administrator::modifypassword(QString pw){
    am->modifyPassword(pw, this->getID());
}

int Administrator::getID(){return ID;}

std::string Administrator::getUsername(){return Username;}

std::string Administrator::getPassword(){return Password;}

int Administrator::approve_or_refuse(Record *record, int approve) {
    Book* book = record->getBook();
    Guest* guest = record->getGuest();
    if(record->getType() == 0){
        if(approve == 1){                                                   //成功借走
        if(book->getOnshelf() == 0){
            return 0;
        }
        bm->modifyInfo(book, "Onshelf", "0");              //0为不在架
        guest->increaseBbook();                                          //已经increase了
        guest->decreaseobook();
        gm->modifyInfo(guest, "bookID"+QString::number(guest->getbBook()), QString::number(book->getID()));
        guest->getbook(book);
        bm->modifyInfo(book, "GuestID1", QString::number(guest->getID()));
        bm->modifyInfo(book, "borrowTime", "NOW()");
        record->modifyResult(0);
        }
        else record->modifyResult(1);

        rm->approve_or_refuse(record, approve);
        tm->deleteRecord(record);
    }
    else if(record->getType() == 1){                                                 //归还
        if(approve == 1){
            if(book->getOnshelf() == 1){
                return 2;
            }
            bm->modifyInfo(book, "Onshelf", "1");              //0表示不在架
            int BID = book->getID(), i;
            Book** books = guest->getbooks();
            for(i =0; i<guest->getbBook(); ++i)
                if(books[i]->getID() == BID)
                    break;
            gm->modifyInfo(guest, "bookID"+QString::number(i+1), "NULL");
            bm->modifyInfo(book, "GuestID1", "NULL");
            guest->decreaseBbook();
            for(int j = i; j<guest->getbBook()+guest->getoBook(); ++j){
                guest->exchangeBookID(j);
                gm->modifyInfo(guest, "bookID"+QString::number(j+1), QString::number(books[j]->getID()));
         }
            bm->modifyInfo(book, "borrowTime", "NULL");
            gm->modifyInfo(guest, "bookID" + QString::number(guest->getbBook()+1), "NULL");
            record->modifyResult(0);
            if(record->getBook()->getAppGuestID()) return record->getBook()->getAppGuestID();
        }
        else record->modifyResult(1);
        rm->approve_or_refuse(record, approve);
        tm->deleteRecord(record);
    }
    else qDebug() << "审核记录时发生未知错误";
    return 1;
}

QSqlDatabase& Administrator::getdb(){
    return db;
}

void Administrator::addBook(Book *book) {
    bm->insertBook(book);
}

void Administrator::deleteBook(Book *book) {
    Guest* guest = NULL;
    for(int i=1; i<=3; ++i){
        if(!(gm->find_guest("bookID"+QString::number(i),QString::number(book->getID())).empty())){
            guest = gm->find_guest("bookID"+QString::number(i), QString::number(book->getID())).front();
            break;
        }
    }
    if(!(guest == NULL)) {                                                  //如果本书已被借走
        int BID = book->getID(), i;
        Book** books = guest->getbooks();
        for(i =0; i<3; ++i){
            if(books[i]->getID() == BID)
                break;
        }
        ++i;
        gm->modifyInfo(guest, "bookID"+QString::number(i), "NULL");
        bm->putBookBack(book);
        for(int j = i; j<guest->getbBook(); ++j){
            guest->exchangeBookID(j);
            gm->modifyInfo(guest, "bookID"+QString::number(j), QString::number(books[j+1]->getID()));
     }
        guest->decreaseBbook();
    }
    bm->dropBook(book);
    return;
}

std::vector<Guest*> Administrator::find_guest(std::string type, std::string value) {
    std::vector<Guest*> guests = gm->find_guest(QString::fromStdString(type),QString::fromStdString(value));
    return guests;
}

std::vector<Record*> Administrator::findRecord(QString type, QString value) {
    std::vector<Record*> records = rm->findRecord("administrator", type, value, QString::number(getID()));
    return records;
}

std::vector<Book*> Administrator::findBook(std::string type, std::string value){
    std::vector<Book*> books = bm->findBook(QString::fromStdString(type), QString::fromStdString(value));
    return books;
}


void Administrator::modifyBook(Book *book, QString column, QString value){
    bm->modifyInfo(book, column, value);
}

void Administrator::modifyGuest(Guest *guest, QString column, QString value){
    gm->modifyInfo(guest, column, value);

}

void Administrator::deleteGuest(Guest *guest){
    gm->dropGuest(guest);
}

int Administrator::getType(){
    return 1;
}
