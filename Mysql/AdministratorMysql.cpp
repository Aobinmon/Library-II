#include "AdministratorMysql.h"

int AdministratorMysql::existUsername(QString username){
    query->exec("select * from administrator where Username = \"" + username + "\"" );
    if(query->next()) return 1;
    query->exec("select * from administrator where ID=" + username);
    if(query->next()) return 2;
    return 0;
}

AdministratorMysql::AdministratorMysql(QSqlDatabase& db):Mysql(db), db(db){}

Administrator* AdministratorMysql::findAd(QString type, QString feature){
    query->exec("select * from Administrator where " + type + "=\"" + feature +"\"");
    if(query->next()){
        int ID = query->value(0).toInt();
        std::string username = query->value(1).toString().toStdString();
        std::string password = query->value(2).toString().toStdString();
        return new Administrator(ID, username, password, db);
    }
}


QString AdministratorMysql::getPassword(QString username){
    query->exec("select Password from Administrator where Username = \"" + username + "\"");
    if(query->next()) return query->value(0).toString();
    query->exec("select Password from Administrator where ID = " + username);
    if(query->next()) return query->value(0).toString();
}

void  AdministratorMysql::modifyPassword(QString password, int ID){
    query->exec("UPDATE Administrator SET Password= \"" + password + "\" where ID=" + QString::number(ID));
}
