#include "SearchBookDialog.h"
#include "core/Guest.h"
#include "core/Administrator.h"
#include <string>
SearchBookDialog::SearchBookDialog(User* user_, QWidget *parent):
    QDialog(parent), user(user_){
    layout = new QGridLayout;
    setcolumn = new QButtonGroup;
    id = new QRadioButton(tr("ID"), this);
    setcolumn->addButton(id, 0);
    column[0] = "ID";
    bookname = new QRadioButton(tr("书名"), this);
    setcolumn->addButton(bookname, 1);
    column[1] = "Bookname";
    writername = new QRadioButton(tr("作者名"), this);
    setcolumn->addButton(writername, 2);
    column[2] = "Writername";
    press = new QRadioButton(tr("出版社"), this);
    column[3] = "Press";
    setcolumn->addButton(press, 3);
    presstime = new QRadioButton(tr("出版时间"), this);
    setcolumn->addButton(presstime, 4);
    column[4] = "Presstime";
    type = new QRadioButton("类型", this);
    column[5] = "Type";
    setcolumn->addButton(type, 5);
    layout->addWidget(id, 1, 2);
    layout->addWidget(bookname, 1, 1);
    layout->addWidget(writername, 1, 3);
    layout->addWidget(press, 1, 4);
    layout->addWidget(presstime, 1, 5);
    layout->addWidget(type, 1, 6);

    browser = new QLineEdit(this);
    browser->setPlaceholderText(tr("请输入需要搜索的信息"));
    layout->addWidget(browser, 2, 1);

    listwidget = new BookListWidget(user);
    browse = new QPushButton("搜索", this);
    layout->addWidget(browse, 2, 2);


    layout->addWidget(listwidget, 3, 1);
    commit = new QPushButton("退出", this);
    layout->addWidget(commit, 7, 1);
    connect(commit, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(this, SIGNAL(signalBrowse(std::string,std::string)), listwidget, SLOT(getbook(std::string,std::string)));
    connect(browse, SIGNAL(clicked(bool)), this, SLOT(push_browse()));


    this->setLayout(layout);

}

void SearchBookDialog::push_browse(){
    delete listwidget;
    listwidget = new BookListWidget(user);
    layout->addWidget(listwidget, 3,1);
    connect(this, SIGNAL(signalBrowse(std::string,std::string)), listwidget, SLOT(getbook(std::string,std::string)));
    int k = setcolumn->checkedId();
    emit signalBrowse(column[k].toStdString(), browser->text().toStdString());
}
