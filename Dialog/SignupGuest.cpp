#include "SignupGuest.h"
#include "core/constant.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QFont>
#include <QDebug>
#include <string>
#include <QtSql/QtSql>

SignupGuestDialog::SignupGuestDialog(QSqlDatabase& db, QWidget *parent):
    QWidget(parent), db(db){
    layout = new QGridLayout(this);
    username = new QLabel(tr("用户名"), this);
    layout->addWidget(username, 0, 0);
    password1 = new QLabel(tr("设置您的密码"), this);
    layout->addWidget(password1, 1, 0);
    password2 = new QLabel(tr("确认您的密码"), this);
    layout->addWidget(password2, 2, 0);

    setusername = new QLineEdit(this);
    setusername->setPlaceholderText(tr("请输入您的用户名"));
    layout->addWidget(setusername, 0, 2);
    setpassword = new QLineEdit(this);
    setpassword->setPlaceholderText(tr("请输入您的密码"));
    setpassword->setEchoMode(QLineEdit::Password);
    layout->addWidget(setpassword, 1, 2);
    confirmpassword = new QLineEdit(this);
    confirmpassword->setPlaceholderText(tr("请再次确认您的密码"));
    confirmpassword->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmpassword, 2, 2);

    submmit = new QPushButton(tr("确认提交"),this);
    layout->addWidget(submmit, 3,2);
    QObject::connect(submmit, SIGNAL(clicked()), this, SLOT(Push_Submmit()));
    setLayout(layout);
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);

    gmysql = new GuestMysql(db);
}

SignupGuestDialog::~SignupGuestDialog(){
}

void SignupGuestDialog::Push_Submmit(){
    bool ok = true;
    if(setusername->text().toStdString() == ""){
        QMessageBox* warning = new QMessageBox(this);
        warning->information(this, tr("ERROR"), tr("用户名不能为空！"), QMessageBox::Ok);
        warning->exec();
        ok = false;
    }
    else if(gmysql->existUsername(setusername->text())){
        QMessageBox* warning = new QMessageBox(this);
        warning->information(this, tr("ERROR"), tr("用户名已被使用！"), QMessageBox::Ok);
        warning->exec();
        ok = false;
        delete warning;
    }
    else{
        QString Password1 = QCryptographicHash::hash((passwordBegin + setpassword->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
        QString Password2 = QCryptographicHash::hash((passwordBegin + confirmpassword->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
        if(ok == true){
        if(Password1 == Password2){
            if(setpassword->text().toStdString().size() >= 6){
            QMessageBox* con = new QMessageBox(this);
            gmysql->addGuest(setusername->text(), Password1);
            int id = (gmysql->find_guest("Username", setusername->text()).front())->getID();
            con->information(this, tr("congratulation"), QString::fromStdString("注册成功！你的用户ID是：\n" + std::to_string(id)), QMessageBox::Ok);
            delete con;
            this->close();
            }
            else{
                QMessageBox* warning = new QMessageBox;
                warning->information(this, tr("warning"), tr("密码不能小于6位！"), QMessageBox::Ok);
            }
        }
        else{
            QMessageBox* warning = new QMessageBox;
            warning->information(this, tr("ERROR"), tr("两次密码输入不一致！"), QMessageBox::Ok);
        }
        }
    }
}
