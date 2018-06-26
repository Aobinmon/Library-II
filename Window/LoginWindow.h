#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include "Mysql/AdministratorMysql.h"
#include "Mysql/GuestMysql.h"

class Loginwindow: public QMainWindow{
    Q_OBJECT
public:
    Loginwindow(QSqlDatabase& db);
private slots:
    void push_login();
    void push_regi();
private:
    QSqlDatabase& db;
    QPixmap *pixmap;
    QLabel* username, *password, *background, *welcome;
    QLineEdit* usr, *pw;
    QPushButton* login, *quit, *regi;
    AdministratorMysql* amysql;
    GuestMysql* gmysql;
};

#endif // LOGINWINDOW_H
