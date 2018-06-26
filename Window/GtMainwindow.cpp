#include "GtMainwindow.h"
#include "Dialog/GuestMessageDialog.h"
#include "Dialog/SearchRecordDialog.h"
#include <QMessageBox>
GtMainWindow::GtMainWindow(Guest* guest_,QSqlDatabase& db, QWidget *parent):
    QMainWindow(parent), guest(guest_), db(db){
    if(guest->getappbook() == 1){
        QMessageBox::information(this, "congratualtions", "你的预约申请已被审核", QMessageBox::Ok);
        guest->modiappbook();
    }
    this->setFixedSize(400, 300);
    welcome = new QLabel("欢迎~", this);
    function[0] = new QAction(tr("查询图书"), this);
    function[2] = new QAction(tr("查看借阅记录"), this);
    function[3] = new QAction("查看个人信息", this);
    bookmenu = new QMenu(tr("    图书    "), this);
    guestmenu = new QMenu("个人信息", this);
    for(int i=0; i<3; ++i) if(i!=1)bookmenu->addAction(function[i]);
    guestmenu->addAction(function[3]);
    menubar = new QMenuBar(this);
    menubar->addMenu(bookmenu);
    menubar->addMenu(guestmenu);

    connect(function[0], SIGNAL(triggered(bool)), this, SLOT(search_book()));
    connect(function[2], SIGNAL(triggered(bool)), this, SLOT(getMyRecord()));

    connect(function[3], SIGNAL(triggered(bool)), this, SLOT(getMyMessage()));


    logout = new QPushButton("注销", this);
    connect(logout, SIGNAL(clicked(bool)), this, SLOT(push_logout()));
    logout->setGeometry(300, 0, 70, 25);
    this->setWindowTitle("ID:  " + QString::number(guest->getID()));
}

void GtMainWindow::search_book(){
    SearchBookDialog* searchDialog = new SearchBookDialog(guest);
    searchDialog->show();
}

void GtMainWindow::push_logout(){
    login = new Loginwindow(db);
    login->show();
    this->close();
}


void GtMainWindow::getMyMessage(){
    GuestMessageDialog* bdialog = new GuestMessageDialog(guest, this);
    bdialog->show();
}

void GtMainWindow::getMyRecord(){
    SearchRecordDialog *srdialog = new SearchRecordDialog(guest, this);
    srdialog->show();
}
