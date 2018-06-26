#ifndef SignupGuestDialog_H
#define SignupGuestDialog_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "Mysql/GuestMysql.h"

class SignupGuestDialog : public QWidget{
    Q_OBJECT
public:
    SignupGuestDialog(QSqlDatabase& db, QWidget* parent = 0);
    ~SignupGuestDialog();
private:
    QSqlDatabase& db;
    QLabel* username, *password1, *password2;
    QLineEdit* setusername, *setpassword, *confirmpassword;
    QPushButton* submmit;
    QGridLayout* layout;
    GuestMysql* gmysql;
private slots:
    void Push_Submmit();
};

#endif // SignupGuestDialog_H
