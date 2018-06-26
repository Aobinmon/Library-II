#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(int type){
    if(type == 1){
        QMessageBox::information(NULL, tr("warning"), tr("不存在该用户"), QMessageBox::Ok);
    }
    else if(type == 2){
        QMessageBox::information(NULL, tr("warning"), tr("密码错误"), QMessageBox::Ok);
    }
    else if(type == 3){
        QMessageBox::information(NULL, tr("warning"), tr("请输入密码"), QMessageBox::Ok);
    }
    else if(type == 4){
        QMessageBox::information(NULL, tr("warning"), tr("请输入用户名"), QMessageBox::Ok);
    }
}
