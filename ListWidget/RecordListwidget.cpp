#include "RecordListwidget.h"
#include <QMessageBox>

RecordListWidget::RecordListWidget(User *user_, QWidget *parent):
    user(user_), QListWidget(parent){
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setIconSize(QSize(114, 160));
    setUniformItemSizes(true);
    setResizeMode(QListWidget::Adjust);
    connect(this, &RecordListWidget::itemDoubleClicked, this, &RecordListWidget::itemclicked);
}


void RecordListWidget::itemclicked(QListWidgetItem *item){
    auto item_ = dynamic_cast<RecordItem*> (item);
    RecordDialog* rdialog = new RecordDialog(item_->getRecord());
    rdialog->show();
}

void RecordListWidget::slotBrowse(QString type_, QString value){
    std::vector<Record*> records;
    Guest* guest;
    Administrator* ad;
    if(user->getType() == 0){
        guest = dynamic_cast<Guest*> (user);
        records = guest->findRecord(type_, value);
    }
    else if(user->getType() == 1){
        ad = dynamic_cast<Administrator*> (user);
        records = ad->findRecord(type_, value);
    }
    if(records.empty()) QMessageBox::information(this, "error", "未查询到相关记录", QMessageBox::Ok);
    else for(int i=0; i<records.size(); ++i){
        this->add_item(records[i], i);
    }
}

void RecordListWidget::add_item(Record *record, int row){
    insertItem(row, new RecordItem(record));
}

Record* RecordItem::getRecord(){return record;}

RecordItem::RecordItem(Record *record_, QListWidget *parent):
    record(record_), QListWidgetItem(parent){
    QString type_;
    if(record->getType() == 1) type_ = "归还";
    else if(record->getType() == 0) type_ = "借阅";
    setText("ID:" + QString::number(record->getID()) + "  " + type_+"\n"+
            "读者:"+QString::fromStdString(record->getGuest()->getUsername()) + "\n"
            + "图书:"+QString::fromStdString(record->getBook()->getBookName()) + "\n"
            +QString::fromStdString("日期：" + record->getTime()));
}

RecordDialog::RecordDialog(Record *record_):
    record(record_){
    QString type_;
    QString result_;
    if(record->getType() == 1) type_ = "归还";
    else if(record->getType() == 0) type_ = "借阅";
    if(record->getResult() == 0) result_ = "通过";
    else if(record->getResult() == 1) result_ = "未通过";

    layout = new QGridLayout(this);
    guest = new QLabel(QString::fromStdString(record->getGuest()->getUsername()) + "(" + QString::number(record->getGuest()->getID()) + ")");
    book = new QLabel(QString::fromStdString(record->getBook()->getBookName()) + "(" + QString::number(record->getBook()->getID()) +")");
    type = new QLabel("类型:" + type_);
    result = new QLabel("结果:" + result_);
    layout->addWidget(guest, 1, 1);
    layout->addWidget(book, 2, 1);
    layout->addWidget(type, 3, 1);
    layout->addWidget(result, 3, 2);
    exit = new QPushButton("退出");

    connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
}
