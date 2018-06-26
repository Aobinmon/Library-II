#include "DeleteBookDialog.h"
#include <QMessageBox>

DeleteBookDialog::DeleteBookDialog(Administrator *ad_):
    ad(ad_){
    layout = new QGridLayout(this);
    notice = new QLabel("请输入需要删除的书籍ID");
    getID = new QLineEdit;
    commit = new QPushButton("确认");
    exit = new QPushButton("退出");
    connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    layout ->addWidget(notice, 1, 1);
    layout->addWidget(getID, 2, 1);
    layout->addWidget(commit, 3, 1);
    layout->addWidget(exit, 3, 2);

    this->setLayout(layout);
}

void DeleteBookDialog::push_commit(){
    if(ad->findBook("ID", getID->text().toStdString()).empty())
        QMessageBox::information(this, "error", "不存在该书ID", QMessageBox::Ok);
    else{
        Book* book = ad->findBook("ID", getID->text().toStdString()).front();
        ad->deleteBook(book);
        if(ad->findBook("ID", getID->text().toStdString()).empty()){
            QMessageBox::information(this, "congratulations", "成功删除", QMessageBox::Ok);
            this->close();
        }
    }
}
