#ifndef LIBRAR_BOOK_H
#define LIBRAR_BOOK_H

#include <string>
#include <vector>
#include "Mysql/Mysql.h"
#include "Guest.h"

class Guest;
class Book {
    std::string BookName;
    int BorrowGuestID, AppGuestID;
    int ID;                                                      //6位，前两位代表类型，中间两位代表特点，最后两位代表编号
    std::string WriterName;
    std::string Press;                         //出版社
    std::string PressTime;                     //出版时间
    int Onshelf;                              //0不在架，1在架
    std::string Position;                      //馆藏位置
    std::string Summary;                       //简介
    std::string Type;                          //类型
    std::string borrowTime;
public:
    Book(int id ,std::string _BookName, std::string _WriterName,std::string position, std::string _Press, std::string _PressTime,
         std::string type,int onshelf, std::string summary, int guestborrow_=0,std::string borrowTime="", int guestapp_=0);//是否在架，馆藏位置，简介，类型？
    int getID();
    std::string getBookName();
    std::string getWriterName();
    std::string getPress();
    std::string getPressTime();
    int getOnshelf();
    int getBorrowGuestID();
    int getAppGuestID();
    std::string getPosition();
    std::string getSummary();
    std::string getType();
    std::string getborrowTime();
};


#endif

