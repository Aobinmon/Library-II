#include "WaitingRecordDialog.h"
#include <QMessageBox>
WaitingRecordDialog::WaitingRecordDialog(Administrator *ad_, std::vector<Record*> record_, QWidget* parent):
    ad(ad_), record(record_), QDialog(parent){
    now = 0;
    tm = new To_doMysql(ad->getdb());
    if(record.empty()){
        QLabel* ok = new QLabel(tr("暂无读者请求"));
        layout = new QGridLayout;
        layout->addWidget(ok, 1, 1);
        QPushButton*exit = new QPushButton(tr("退出"),this);
        layout->addWidget(exit, 2, 2);
        QObject::connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
        this->setLayout(layout);
    }
    else{
        recordnow = record[now];
        done = false;
        layout = new QGridLayout;
        book = new QLabel(this);
        user = new QLabel(this);
        const QString book_ = QString::fromStdString(recordnow->getBook()->getBookName() + "("
                                                     + std::to_string(recordnow->getBook()->getID()) + ")");
        book->setText(book_);
        layout->addWidget(book, 1, 1);
        const QString user_ = QString::fromStdString(recordnow->getGuest()->getUsername() + "("
                                                     + std::to_string(recordnow->getGuest()->getID()) +")");
        user->setText(user_);
        layout->addWidget(user, 2, 1);

        type = new QLabel(this);
        if(recordnow->getType() == 1) type->setText("归还");
        else if(recordnow->getType()==0) type->setText("借阅");
        layout->addWidget(type, 3, 1);
        approve = new QPushButton(tr("同意"));
        refuse = new QPushButton(tr("拒绝"));
        layout->addWidget(approve, 4, 1);
        layout->addWidget(refuse, 4, 2);

        connect(approve, SIGNAL(clicked(bool)), this, SLOT(push_approve()));
        connect(refuse, SIGNAL(clicked(bool)), this, SLOT(push_refuse()));
        this->setLayout(layout);
    }
}

void WaitingRecordDialog::push_approve(){
    int k = ad->approve_or_refuse(recordnow, 1);
    if(k){
        done = true;
        if(k == 2) QMessageBox::information(this, "error", "该书已在架，建议拒绝该请求！", QMessageBox::Ok);
        else{
            if(k != 1){
            Guest* gtmp = ad->find_guest("ID", std::to_string(k)).front();
            Record* rec = new Record(gtmp, recordnow->getBook(), 0);
            ad->modifyBook(recordnow->getBook(), "GuestID2", "NULL");
            tm->addRecord(rec);
            rec->modiID(tm->get_lastID());
            ad->modifyGuest(gtmp, "appbook", "1");
            record.push_back(rec);
           gtmp->decreaseobook();
            }
            QMessageBox ok;
            ok.information(this, tr("congratulations"), tr("成功审核"), QMessageBox::Ok);
            next();
        }
    }
    else {
        QMessageBox::information(this, "error", "该书已被借走，建议拒绝该请求", QMessageBox::Ok);
    }
}

void WaitingRecordDialog::next(){
    if(done){
            done = false;
            ++now;
            if(now >= record.size()){
                delete book;
                delete user;
                delete approve;
                delete refuse;
                delete type;
                delete recordnow;
                QLabel* ok = new QLabel(tr("已处理完所有请求！"));
                layout->addWidget(ok, 1, 1);
                QPushButton*exit = new QPushButton(tr("退出"),this);
                layout->addWidget(exit, 2, 2);
                QObject::connect(exit, SIGNAL(clicked(bool)), this, SLOT(close()));
            }
            else{
                Guest* gtmp = ad->find_guest("ID", std::to_string(record[now]->getGuest()->getID())).front();
                Book* btmp = ad->findBook("ID", std::to_string(record[now]->getBook()->getID())).front();
                delete  recordnow;
                recordnow = new Record(gtmp, btmp, record[now]->getType(), record[now]->getID());
                qDebug() << "RecordID:" << recordnow->getID();
                delete book;
                delete user;

                user = new QLabel(this);
                book = new QLabel(this);
                user->setText("读者：" + QString::fromStdString(gtmp->getUsername() + "(") + QString::number(gtmp->getID()) + ")");
                layout->addWidget(user, 2, 1);
                book->setText("图书：" + QString::fromStdString(btmp->getBookName() + "(") + QString::number(btmp->getID()) +")");
                layout->addWidget(book, 1, 1);


                if(recordnow->getType() == 1) type->setText("归还");
                else type->setText("借阅");
            }
        }
    else{
        QMessageBox warning;
        warning.information(this, tr("warning"), tr("请先处理完这次请求"), QMessageBox::Ok);
    }
}

void WaitingRecordDialog::push_refuse(){
    if(ad->approve_or_refuse(recordnow, 0)){
        QMessageBox::information(this, "congratulations", "成功拒绝", QMessageBox::Ok);
        done = true;
        next();
    }
}



