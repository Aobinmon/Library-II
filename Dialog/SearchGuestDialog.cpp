#include "SearchGuestDialog.h"
#include <QMessageBox>
SearchGuestDialog::SearchGuestDialog(Administrator* ad_, QWidget *parent):
    QDialog(parent), ad(ad_){
    setUI();
    connect(commit, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(browse, SIGNAL(clicked(bool)), this, SLOT(push_browse()));
    connect(this, SIGNAL(signalBrowse(std::string,std::string)), listwidget, SLOT(slotBrowse(std::string,std::string)));
}

void SearchGuestDialog::setUI(){
    layout = new QGridLayout;
    ID = new QRadioButton("ID");
    Username = new QRadioButton("用户名");
    setcolumn = new QButtonGroup;
    setcolumn->addButton(ID, 0);
    setcolumn->addButton(Username, 1);
    layout->addWidget(ID, 1, 1);
    layout->addWidget(Username, 1, 2);
    setvalue = new QLineEdit;
    setvalue->setPlaceholderText("请输入要检索的信息");
    layout->addWidget(setvalue, 2, 1);

    browse = new QPushButton("搜索");
    commit = new QPushButton("退出");
    layout->addWidget(browse, 2, 3);

    listwidget = new GuestListWidget(ad);
    layout->addWidget(listwidget, 3, 1, 4, 4);

    commit = new QPushButton("退出");
    layout->addWidget(commit, 8, 2);

    this->setLayout(layout);
}

void SearchGuestDialog::push_browse(){
    delete listwidget;
    listwidget = new GuestListWidget(ad, this);
    layout->addWidget(listwidget,3, 1, 4, 4);
    connect(this, SIGNAL(signalBrowse(std::string,std::string)), listwidget, SLOT(slotBrowse(std::string,std::string)));
    std::string type_;
    std::string value_ = setvalue->text().toStdString();
    int k = setcolumn->checkedId();
    if(k == -1) if(k == -1) QMessageBox::information(this, "warning", "请选择查询类型", QMessageBox::Ok);
    else{
        if(k == 0) type_ = "ID";
        else if (k == 1) type_ = "Username";
        emit signalBrowse(type_, value_);
    }
}
