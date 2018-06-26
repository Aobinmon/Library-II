#include "LoginWindow.h"
#include "ErrorMessage.h"
#include "Dialog/SignupAd.h"
#include "core/Administrator.h"
#include "core/Guest.h"
#include "AdMainwindow.h"
#include "Dialog/SignupGuest.h"
#include "GtMainwindow.h"
#include "core/constant.h"
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QCryptographicHash>
#include <QtSql/QtSql>


Loginwindow::Loginwindow(QSqlDatabase& db) : db(db){
    this->setGeometry(720, 400, 540, 300);
    pixmap = new QPixmap();
    pixmap->load("C:/Qt/test/Book-back.jpg");
    background = new QLabel(this);
    background->setPixmap(*pixmap);
    background->setGeometry(0, 0, 540, 300);
    welcome = new QLabel(tr("欢迎使用图书管理系统, 请登录"),this);
    welcome->setGeometry(50, 20, 520, 70);
    username = new QLabel(tr("用户ID"), this);
    username->setGeometry(100, 120, 70, 36 );
    password = new QLabel(tr("密码"), this);
    password->setGeometry(100, 170, 70, 36);
    usr = new QLineEdit(this);
    usr->setPlaceholderText(tr("请输入用户ID"));
    usr->setGeometry(200, 120, 200, 36);
    pw = new QLineEdit(this);
    pw->setGeometry(200, 170, 200, 36);
    pw->setPlaceholderText(tr("请输入密码"));
    this->pw->setEchoMode(QLineEdit::Password);
    login = new QPushButton(tr("登录"), this);
    login->setGeometry(100, 220, 70, 36);
    quit = new QPushButton(tr("退出"), this);
    quit->setGeometry(250, 220, 70, 36);
    login->setShortcut(Qt::Key_Enter);
    quit->setShortcut(Qt::Key_Escape);
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(login, SIGNAL(clicked()), this, SLOT(push_login()));
    regi = new QPushButton(tr("注册"), this);
    regi->setGeometry(350, 220, 70, 36);
    QObject::connect(regi, SIGNAL(clicked()), this, SLOT(push_regi()));
    amysql = new AdministratorMysql(db);
    gmysql = new GuestMysql(db);
}

void Loginwindow::push_login(){
    int type = 0;
    if(usr->text() == "") type = 4;
    else if(pw->text() == "") type = 3;
    else{        
        if(amysql->existUsername(usr->text())) type = -1;
        else{
            if(gmysql->existUsername(usr->text())) type = 0;
            else type = 1;
        }
        if(type <= 0){
            if(type == 0){
                QString standardPassword = gmysql->getPassword(usr->text());
                QString thePassword = QCryptographicHash::hash((passwordBegin + pw->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
                if(standardPassword != thePassword) type = 2;
            }
            else if(type == -1){
                QString standardPassword = amysql->getPassword(usr->text());
                QString thePassword = QCryptographicHash::hash((passwordBegin + pw->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
                if(standardPassword != thePassword) type = 2;
            }
        }
    }
    if(type > 0){
        ErrorMessage* error = new ErrorMessage(type);
    }
    else if(type == 0){                                    //用户登录
        Guest* guest;
        if(gmysql->existUsername(usr->text()) == 2)  guest = gmysql->find_guest("ID", usr->text()).front();
        else guest = gmysql->find_guest("Username", usr->text()).front();
        GtMainWindow* guestmainwindow = new GtMainWindow(guest, db);
        guestmainwindow->show();
        this->close();
    }
    else if(type == -1){
        Administrator* ad;
        if(amysql->existUsername(usr->text()) == 2)  ad = amysql->findAd("ID", usr->text());
        else ad = amysql->findAd("Username", usr->text());
        if(ad->getType()){
            AdMainWindow* admainwindow = new AdMainWindow(ad, db);
            admainwindow->show();
            this->close();
        }
    }
    else{
        QMessageBox* con = new QMessageBox(this);
        con->information(this, tr("Error!"), tr("未知错误！"), QMessageBox::Ok);
        delete con;
    }
}

void Loginwindow::push_regi(){
    SignupGuestDialog* regiwindow = new SignupGuestDialog(db);
    regiwindow->show();
}
