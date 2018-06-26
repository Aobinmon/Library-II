#include "Window/LoginWindow.h"
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <string>
#include <iostream>
using namespace std;


int main(int argc, char** argv){
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Library_manager");
    db.setUserName("root");
    db.setPassword("123456");
    db.open();
    Loginwindow w(db);
     w.show();

    return a.exec();
}
