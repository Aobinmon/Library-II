#include "Administrator.h"
#include "Guest.h"
#include "Book.h"
#include "Record.h"
#include <QString>

Book::Book(int id, std::string _BookName, std::string _WriterName, std::string position, std::string _Press,
           std::string _PressTime, std::string type, int onshelf, std::string summary, int guestborrow_,  std::string borrowTime_, int guestapp_) {
    ID = id;
    borrowTime = borrowTime_;
    Onshelf = onshelf;
    BookName = _BookName;
    WriterName = _WriterName;
    Press = _Press;
    PressTime = _PressTime;
    Position = position;
    Type = type;
    Summary = summary;
    BorrowGuestID = guestborrow_;
    AppGuestID = guestapp_;
}

int Book::getID() {
    return ID;
}

std::string Book::getborrowTime(){
    return borrowTime;
}

std::string Book::getBookName() {
    return BookName;
}

int Book::getOnshelf() {
    return Onshelf;
}

std::string Book::getPosition() {
    return Position;
}

std::string Book::getPress() {
    return Press;
}

std::string Book::getPressTime() {
    return PressTime;
}

std::string Book::getSummary() {
    return Summary;
}

std::string Book::getType() {
    return Type;
}

std::string Book::getWriterName() {
    return WriterName;
}

int Book::getAppGuestID(){return AppGuestID;}

int Book::getBorrowGuestID(){return BorrowGuestID;}

