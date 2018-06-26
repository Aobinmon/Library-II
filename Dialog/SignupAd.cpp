#include "SignupAd.h"
#include "core/constant.h"
#include <QGridLayout>
#include <QDir>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QtSql/QtSql>
SignupAdDialog::SignupAdDialog(){
    layout = new QGridLayout(this);
    username = new QLabel(tr("用户名"),this);
    password1 = new QLabel(tr("输入密码"),this);
    password2 = new QLabel(tr("确认密码"),this);
    setusername = new QLineEdit(this);
    setpassword= new QLineEdit(this);
    setpassword->setEchoMode(QLineEdit::Password);
    confirmpassword = new QLineEdit(this);
    submit = new QPushButton(tr("确认"),this);
    confirmpassword->setEchoMode(QLineEdit::Password);
    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(push()));
    layout->addWidget(username, 0, 0);
    layout->addWidget(password1, 1, 0);
    layout->addWidget(password2, 2, 0);
    layout->addWidget(setusername, 0, 1);
    layout->addWidget(setpassword, 1, 1);
    layout->addWidget(confirmpassword, 2, 1);
    layout->addWidget(submit, 3,  2);
    setLayout(layout);
}

void SignupAdDialog::push(){
    QSqlQuery query;
    query.exec(QString::fromStdString("select * from Administrator where Username=\"" + setusername->text().toStdString() + "\""));
    if(setusername->text().toStdString() == ""){
        QMessageBox message(this);
        message.information(this, tr("warning"), tr("请输入用户名！"), QMessageBox::Ok);
    }
    else if(setpassword->text().toStdString() ==  ""){
        QMessageBox message(this);
        message.information(this, tr("warning"), tr("请输入密码！"), QMessageBox::Ok);
    }
    else if(setpassword->text() == confirmpassword->text()){
        query.prepare("INSERT INTO Administrator(Username, Password)" "VALUES(:Username, :Password)");
        query.bindValue(":Username", setusername->text());
        QString password = QCryptographicHash::hash((passwordBegin + setpassword->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
        query.bindValue(":Password", password);
        bool suc = query.exec();
        QMessageBox message;
        if(suc){
            message.information(this, tr("congratuations"), tr("创建成功！"), QMessageBox::Ok);
            this->close();
        }
            else message.information(this, tr("error"), tr("未知错误！"), QMessageBox::Ok);
    }
    else{
        QMessageBox message(this);
        message.information(this, tr("warning"), tr("两次输入的密码不一致!"), QMessageBox::Ok);
    }
}


SignupAdDialog::~SignupAdDialog(){
    delete password1;
    delete password2;
    delete username;
    delete setusername;
    delete confirmpassword;
    delete submit;
}
