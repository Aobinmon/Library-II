#pragma once


#include <string>
#include "Guest.h"
#include "Book.h"
#include <vector>


class Guest;
class Book;
class Record {
    int ID;
    std::string time;
    Guest* guest;
    Book* book;
    int type;                                   //0---借阅，1--归还
    int result;                                //0---通过，1--未通过, 2--未审核
public:
    Record(Guest* _guest, Book* _book, int _type, int id=0, int result_ =2, std::string _time="");
    Guest* getGuest();
    Book* getBook();
    int getType();
    int getID();
    int getResult();
    void modifyResult(int result_);
    std::string getTime();
    void modiID(int id);
};
