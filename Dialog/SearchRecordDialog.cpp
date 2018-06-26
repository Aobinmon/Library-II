#include "SearchRecordDialog.h"
#include <QMessageBox>
SearchRecordDialog::SearchRecordDialog(User* user_,  QWidget *parent):
    user(user_), QDialog(parent){
    layout = new QGridLayout(this);
    note = new QLabel("note：类型搜索：1---归还，0---借阅");
    layout->addWidget(note, 1, 2);
    c[0] = "GuestID";
    c[1] = "GuestName";
    c[2] = "BookID";
    c[3] = "BookName";
    c[4] = "Time";
    c[5] = "Type";
    column = new QLabel("请选择关键词类型");
    setcolumn = new QButtonGroup;
    int j;
    if(user->getType() == 1) j=0;
    else if(user->getType() == 0) j = 2;
    for(int i=0; i+j<6; ++i){
        setc[i+j] = new QRadioButton(c[i+j]);
        setcolumn->addButton(setc[i+j], i+j);
        layout->addWidget(setc[i+j], 2, i+1);
    }
    layout->addWidget(column, 1, 1);
    setvalue = new QLineEdit;
    setvalue->setPlaceholderText("如果是时间，请按照标准格式\"xxxx-xx-xx\"");
    layout->addWidget(setvalue, 3, 1);

    browse = new QPushButton("搜索");
    layout->addWidget(browse, 3, 2);
    connect(browse, SIGNAL(clicked(bool)), this, SLOT(push_browse()));

    exit = new QPushButton("退出");
    connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
    layout->addWidget(exit, 5, 2);

    listwidget = new RecordListWidget(user, this);
    layout->addWidget(listwidget, 4, 1);
    this->setLayout(layout);
    connect(this, SIGNAL(signalBrowse(QString,QString)), listwidget, SLOT(slotBrowse(QString,QString)));
}

void SearchRecordDialog::push_browse(){
    delete listwidget;
    listwidget = new RecordListWidget(user, this);
    layout->addWidget(listwidget, 4,1 );
    connect(this, SIGNAL(signalBrowse(QString,QString)), listwidget, SLOT(slotBrowse(QString,QString)));
    int k = setcolumn->checkedId();
    if(k == -1 && setvalue()->text()!="") if(k == -1) QMessageBox::information(this, "warning", "请选择查询类型", QMessageBox::Ok);
    else emit signalBrowse(c[k], setvalue->text());
}
