#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <QString>
class User{
public:
    int ID;
    std::string Password;
    std::string Username;
    User(std::string username, int id, std::string password);
    virtual ~User(){};
    virtual int getType() = 0;
    virtual void modifypassword(QString pw) = 0;

};

#endif
