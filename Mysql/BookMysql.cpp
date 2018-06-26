#include "BookMysql.h"

BookMysql::BookMysql(QSqlDatabase& db) : Mysql(db), db(db){
}

void BookMysql::modifyInfo(Book* book, QString column,QString info){
    if(info == "NULL" || info == "NOW()") query->exec("update books SET " + column + "=" + info +" where ID=" + QString::number(book->getID()));
    else query->exec("update books SET " + column + "=" + "\"" + info +"\" where ID=" + QString::number(book->getID()));
}

void BookMysql::insertBook(Book *book){
    int id;
    query->exec(QString::fromStdString("select ID from books where type = " + book->getType()));
    if(query->last()) id = query->value(0).toInt()+1;
    else{
        query->exec("select ID from books");
        if(query->last()){
            int tmp = (query->value(0).toInt())/100+1;
            id = tmp*100+1;
        }
        else id = 180101;
    }
    QString bookname=QString::fromStdString(book->getBookName());
    QString writername=QString::fromStdString(book->getWriterName());
    QString press=QString::fromStdString(book->getPress());
    QString presstime=QString::fromStdString(book->getPressTime());
    QString type=QString::fromStdString(book->getType());
    QString position=QString::fromStdString(book->getPosition());
    QString summary=QString::fromStdString(book->getSummary());
    query->prepare("INSERT INTO books (ID, Bookname, Writername, Press, PressTime, Type, Position, Onshelf, Summary) VALUES(?,?,?,?,?,?,?,?,?)");
    query->bindValue(0, id);
    query->bindValue(1, bookname);
    query->bindValue(2, writername);
    query->bindValue(3, press);
    query->bindValue(4, presstime);
    query->bindValue(5, type);
    query->bindValue(6, position);
    query->bindValue(7, 1);
    query->bindValue(8, summary);
    if(query->exec()) qDebug() << "OK";
    else qDebug() << "error!";
}


void BookMysql::dropBook(Book *book){
    query->exec("DELETE from Books where ID="+QString::number(book->getID()));
}

void BookMysql::putBookBack(Book* book){
    query->exec("update books set GuestID1=NULL where ID=" + QString::number(book->getID()));
}

std::vector<Book*> BookMysql::findBook(QString type, QString value){
    std::vector<Book*> books;
    gm = new GuestMysql(db);
    if(value ==  "") query->exec("select * from books");
    else query->exec("select * from books where " + type + "=\"" + value+"\"");
    while(query->next()){
        int id = query->value(0).toInt();
        std::string bookname = query->value(1).toString().toStdString();
        std::string writername = query->value(2).toString().toStdString();
        std::string press = query->value(3).toString().toStdString();
        std::string presstime = query->value(4).toString().toStdString();
        std::string type = query->value(5).toString().toStdString();
        std::string position = query->value(6).toString().toStdString();
        std::string summary = query->value(8).toString().toStdString();
        int onshelf = query->value(7).toInt();
        int GuestID1 = query->value(9).toInt();
        int GuestID2 = query->value(10).toInt();
        std::string borrowtime = query->value(11).toString().toStdString();
        if(GuestID1 == 0) books.push_back(new Book(id, bookname, writername,position, press, presstime, type, onshelf,summary));
        else if(GuestID2 == 0) {
            books.push_back(new Book(id, bookname, writername, position, press, presstime, type, onshelf, summary, GuestID1, borrowtime));
        }
        else{
            books.push_back(new Book(id, bookname, writername, position, press, presstime, type, onshelf, summary, GuestID1,borrowtime, GuestID2));
        }
    }

    return books;
}
