#include "GuestMessageDialog.h"
#include <QMessageBox>
GuestMessageDialog::GuestMessageDialog(Guest *guest_, QWidget* parent):
    guest(guest_), QDialog(parent){
    setUI();
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(modify, SIGNAL(clicked(bool)), this, SLOT(push_modify()));
}

void GuestMessageDialog::setUI(){
    layout = new QGridLayout;
    label1 = new QLabel("你现在已借的书有：");
    books1 = new BookListWidget(guest);
    books1->getbook("GuestID1", std::to_string(guest->getID()));
    label2 = new QLabel("你现在预约的书有：");
    ID_ = new QLabel("ID : " + QString::number(guest->getID()));
    Username_ = new QLabel("用户名 : " + QString::fromStdString(guest->getUsername()));
    books2 = new BookListWidget(guest);
    books2->getbook("GuestID2", std::to_string(guest->getID()));
    modify = new QPushButton("修改信息");
    layout->addWidget(ID_, 1, 1);
    layout->addWidget(Username_, 1, 2);
    layout->addWidget(label1, 2, 1);
    layout->addWidget(books1, 3, 1);
    layout->addWidget(label2, 5, 1);
    layout->addWidget(books2, 6, 1);
    layout->addWidget(modify, 6, 2);
    exit = new QPushButton("退出");
    layout->addWidget(exit, 5, 2);
    this->setLayout(layout);
}

void GuestMessageDialog::push_modify(){
    delete label1;
    delete label2;
    delete books1;
    delete books2;
    delete modify;
    delete Username_;
    delete exit;
    setun = new QLineEdit;
    setun->setPlaceholderText("目前用户名: " + QString::fromStdString(guest->getUsername()));
    setpw = new QLineEdit;
    setpw->setEchoMode(QLineEdit::Password);
    setpw->setPlaceholderText("设置密码");
    confirmpw = new QLineEdit;
    confirmpw->setEchoMode(QLineEdit::Password);
    confirmpw->setPlaceholderText("确认密码");
    layout->addWidget(setun, 1, 1);
    layout->addWidget(setpw, 2, 1);
    layout->addWidget(confirmpw, 3, 1);
    commit = new QPushButton("确认");
    layout->addWidget(commit, 4, 1);
    connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));
}


void GuestMessageDialog::push_commit(){
    if(setun->text() == ""){
        QMessageBox::information(this, "error", "请输入用户名", QMessageBox::Ok);
    }
    else if(guest->existUsername(setun->text()) && guest->getUsername()!=setun->text().toStdString()){
        QMessageBox::information(this, "error", "用户名已经存在！",QMessageBox::Ok);
    }
    else if(setpw->text() == "" || confirmpw->text() == ""){
        QMessageBox::information(this, "error", "请输入密码", QMessageBox::Ok);
    }
    else if(setpw->text() != confirmpw->text()){
        QMessageBox::information(this, "error", "两次密码输入不一致", QMessageBox::Ok);
    }
    else if(setpw->text().size() < 6){
        QMessageBox::information(this, "error", "密码不能小于六位", QMessageBox::Ok);
    }
    else {
        QString password = QCryptographicHash::hash((passwordBegin + setpw->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
        guest->modifypassword(password);
        guest->modifyUsername(setun->text());
        QMessageBox::information(this, "congratualtions", "修改成功", QMessageBox::Ok);
        this->close();
    }
}
