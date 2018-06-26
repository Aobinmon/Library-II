#include "AdMainwindow.h"
#include "Dialog/SignupGuest.h"
#include "Dialog/DeleteGuestDialog.h"
#include "Dialog/ChangeGuestDialog.h"
#include "Listwidget/BookListwidget.h"
#include "Mysql/To_domysql.h"
#include "Dialog/SearchBookDialog.h"
#include "Dialog/SignupAd.h"
#include "Dialog/SearchGuestDialog.h"
#include "Dialog/AddBookDialog.h"
#include "Dialog/ModipwDialog.h"
#include "Dialog/DeleteBookDialog.h"
#include "Dialog/SearchRecordDialog.h"

void AdMainWindow::getToDo(){
    To_doMysql todo(db);
    std::vector<Record*> records = todo.get_all();
    to_do = new WaitingRecordDialog(ad, records, this);
    to_do->setGeometry(100, 70, 150, 70);
    to_do->show();
}


AdMainWindow::AdMainWindow(Administrator* ad_, QSqlDatabase& db) : ad(ad_), db(db){
    this->setFixedSize(400, 300);
    welcome = new QLabel(tr("欢迎~"), this);
    this->setCentralWidget(welcome);
    Reader_function[0] = new QAction("添加读者", this);
    QObject::connect(Reader_function[0], SIGNAL(triggered()), this, SLOT(add_guest()));
    Reader_function[1] = new QAction("删除读者", this);
    QObject::connect(Reader_function[1], SIGNAL(triggered()), this, SLOT(delete_guest()));
    Reader_function[3] = new QAction("查询读者信息", this);
    QObject::connect(Reader_function[3], SIGNAL(triggered()), this, SLOT(search_guest()));
    Book_function[0] = new QAction("增加图书", this);
    QObject::connect(Book_function[0], SIGNAL(triggered()), this, SLOT(add_book()));
    Book_function[1] = new QAction("删减图书", this);
    QObject::connect(Book_function[1], SIGNAL(triggered()), this, SLOT(delete_book()));
    Book_function[3] = new QAction("查询图书信息", this);
    QObject::connect(Book_function[3], SIGNAL(triggered()), this, SLOT(search_book()));
    Record_function = new QAction("查询记录", this);
    QObject::connect(Record_function, SIGNAL(triggered()), this, SLOT(search_record()));
    addAdministrator = new QAction("添加管理员", this);
    QObject::connect(addAdministrator, SIGNAL(triggered()), this, SLOT(add_ad()));
    modiPassword = new QAction("修改本管理员密码", this);
    connect(modiPassword, SIGNAL(triggered(bool)), this, SLOT(change_password()));
    menu[0] = new QMenu("   读者   ");
    for(int i=0; i<4; ++i) if(i!=2)menu[0]->addAction(Reader_function[i]);
    menu[1] = new QMenu("   图书   ");
    for(int i=0; i<4; ++i)if(i!=2) menu[1]->addAction(Book_function[i]);
    menu[2] = new QMenu("   记录   ");
    menu[2]->addAction(Record_function);
    menu[3] = new QMenu("   其它   ");
    menu[3]->addAction(addAdministrator);
    menu[3]->addAction(modiPassword);
    for(int i=0; i<4; ++i) menuBar()->addMenu(menu[i]);
    this->setWindowTitle("ID："+QString::number(ad->getID()));

    logout = new QPushButton("注销", this);
    connect(logout, SIGNAL(clicked(bool)), this, SLOT(push_logout()));
    logout->setGeometry(300, 0, 70, 25);
    getToDo();
}

void AdMainWindow::add_guest(){
    SignupGuestDialog* add = new SignupGuestDialog(db);
    add->show();
}
void AdMainWindow::delete_guest(){
    DeleteGuestDialog* del = new DeleteGuestDialog(ad);
    del->show();
}

void AdMainWindow::change_password(){
    ModifyPasswordDialog* mpd = new ModifyPasswordDialog(ad);
    mpd->show();
}
void AdMainWindow::search_record(){
    SearchRecordDialog* recorddialog = new SearchRecordDialog(ad, this);
    recorddialog->show();
}

void AdMainWindow::search_book(){
    SearchBookDialog *result = new SearchBookDialog(ad);
    result->show();
}

void AdMainWindow::push_logout(){
    login = new Loginwindow(db);
    login->show();
    this->close();
}

void AdMainWindow::add_book(){
    AddBookDialog* abDialog = new AddBookDialog(ad, this);
    abDialog->show();
}

void AdMainWindow::delete_book(){
    DeleteBookDialog* dbdialog = new DeleteBookDialog(ad);
    dbdialog->show();
}

void AdMainWindow::search_guest(){
    SearchGuestDialog* SGdialog = new SearchGuestDialog(ad);
    SGdialog->show();
}

void AdMainWindow::add_ad(){
    SignupAdDialog* addAd = new SignupAdDialog;
    addAd->show();
}
