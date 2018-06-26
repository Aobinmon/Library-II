#include "record.h"

Record::Record(Guest *_guest, Book *_book, int  _type, int id, int result_, std::string _time):
    ID(id), time(_time), guest(_guest), book(_book), type(_type), result(result_){}

Guest* Record::getGuest(){
    return guest;
}

int Record::getResult(){
    return result;
}

std::string Record::getTime(){
    return time;
}

Book* Record::getBook(){
    return book;
}

int Record::getType(){
    return type;
}

int Record::getID(){
    return ID;
}

void Record::modifyResult(int result_){
    result = result_;
}

void Record::modiID(int id){
    ID = id;
}
