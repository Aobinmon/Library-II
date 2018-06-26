#include "GuestMysql.h"
#include<iostream>
#include "core/Guest.h"
#include<QString>
#include "core/constant.h"
int GuestMysql::existUsername(QString username){
    query->exec("select * from Guest where Username=\"" + username +"\"");//用户名登录
    if(query->next()) return 1;
    query->exec("select * from Guest where ID="+username);//ID登录
    if(query->next()) return 2;
    return 0;//都不存在
}
QString GuestMysql::getPassword(QString username){
    if(!existUsername(username))
        return "";
    if(existUsername(username)==1){
        query->exec("select Password from Guest where Username=\"" + username +"\"");
        if(query->next()) return query->value(0).toString();
    }
   if(existUsername(username)==2)
   {
    query->exec("select Password from Guest where ID="+username);
    if(query->next()) return query->value(0).toString();
   }
}

GuestMysql::GuestMysql(QSqlDatabase& db):Mysql(db), db(db){
}
std::vector<Guest*> GuestMysql::find_guest(QString type,QString feature){
    std::vector<Guest*> guestlist;
    bm = new BookMysql(db);
    if(feature == "") query->exec("select * from Guest");
    else if(type=="ID"||type=="bbook")
        query->exec("select* from Guest where "+type+"="+feature);
    else
        query->exec("select* from Guest where "+type+"=\""+feature+"\"");
     if(query->next()){
        do{
             int id=query->value(0).toInt();
            std::string username=query->value(1).toString().toStdString();
            std::string password=query->value(2).toString().toStdString();
            int bbook=query->value(3).toInt();
            int appbook = query->value(8).toInt();
            int books[3] = {0};
            for(int i=0; i<bbook; ++i){
                books[i] = query->value(4+i).toInt();
            }
            int obook_ = query->value(7).toInt();
            Book ** Books;
            Books = new Book* [3];
            for(int j=0; books[j]!=0&&j<3; ++j){
                Book *tmp = bm->findBook("ID", QString::number(books[j])).front();
                Books[j] = tmp;
            }
            guestlist.push_back(new Guest(id, username, password, bbook, Books, obook_, db, appbook));
         }while(query->next());
    }
    return guestlist;
}

std::vector<Guest*> GuestMysql::browse_guest(QString type, QString feature){
    std::vector<Guest*> guestlist;
    int len=feature.length();
    int len0=len/3;
    QString string0=feature.mid(0,len0);
    QString string1=feature.mid(len0,2*len0);
    QString string2=feature.mid(2*len0);
    if(type=="id"||type=="bbook")
        query->exec("select * from Guest where "+type+" like %"+string0+"% or "+type+" like %"
               +string1+"% or "+type+" like %"+string2+"%");
    else
         query->exec("select * from Guest where "+type+" like %\""+string0+"\"% or "+type+" like %\""
               +string1+"\"% or "+type+" like %\""+string2+"\"%");
    if(query->next()){
        do{
            int id=query->value(0).toInt();
            std::string username=query->value(1).toString().toStdString();
            std::string password=query->value(2).toString().toStdString();
            int bbook=query->value(3).toInt();
            int books[3] = {0};
            for(int i=0; i<bbook; ++i){
                books[i] = query->value(4+i).toInt();
            }
            Book ** Books;
            Books = new Book* [3];
            int obook_ = query->value(7).toInt();
            int abook = query->value(8).toInt();
            for(int j=0; books[j]!=0&&j<3; ++j){
                Book *tmp = bm->findBook("ID", QString::number(books[j])).front();
                Books[j] = tmp;
                guestlist.push_back(new Guest(id, username, password, bbook, Books, obook_, db, abook));
            }
            return guestlist;
        }while(query->next());
    }
}

void GuestMysql::modifyInfo(Guest* guest, QString column, QString value){
    if(value == "NULL")
        query->exec("update guest SET " + column + " = " + value + " where ID = " + QString::number(guest->getID()));
    else
    query->exec("update guest SET " + column + " = \"" + value + "\" where ID = " + QString::number(guest->getID()));
}

void GuestMysql::dropGuest(Guest *guest){
    query->exec("delete from guest where ID=" + QString::number(guest->getID()));
}

void GuestMysql::addGuest(QString Username, QString Password){
    query->exec("insert into guest ( Username, Password, bBook, obook ) "
               "VALUES"
               "(\"" + Username + "\", \"" + Password + "\", 0, 0 )");
}
