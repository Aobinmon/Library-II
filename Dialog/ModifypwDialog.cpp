#include "ModipwDialog.h"
#include "core/constant.h"
#include <QMessageBox>
ModifyPasswordDialog::ModifyPasswordDialog(User *user_):
    user(user_){
    layout = new QGridLayout(this);
    pw1 = new QLabel("设置新密码", this);
    pw2 = new QLabel("确认新密码", this);
    setpw = new QLineEdit;
    confirmpw = new QLineEdit;
    setpw->setEchoMode(QLineEdit::Password);
    confirmpw->setEchoMode(QLineEdit::Password);
    commit = new QPushButton("确认");
    layout->addWidget(pw1, 1, 1);
    layout->addWidget(setpw, 1, 2);
    layout->addWidget(pw2, 2, 1);
    layout->addWidget(confirmpw, 2, 2);
    layout->addWidget(commit, 3, 2);

    connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));

    this->setLayout(layout);
}

void ModifyPasswordDialog::push_commit(){
    QString pw1 = QCryptographicHash::hash((passwordBegin + setpw->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
    QString pw2 = QCryptographicHash::hash((passwordBegin + confirmpw->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
    if(pw1 == "" || pw2 == "") QMessageBox::information(this, "error", "请输入密码", QMessageBox::Ok);
    else if(pw1 == pw2){
        if(setpw->text().size() >= 6){
            user->modifypassword(pw1);
            QMessageBox::information(this, "congratulations", "修改成功", QMessageBox::Ok);
            this->close();
        }
        else  QMessageBox::information(this, "error", "密码不能小于六位", QMessageBox::Ok);
    }
    else QMessageBox::information(this, "error", "两次输入的密码不一致", QMessageBox::Ok);
}
