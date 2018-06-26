#include "GuestListwidget.h"
#include "Dialog/GuestMessageDialog.h"
#include <QMessageBox>
#include <string>
GuestListWidget::GuestListWidget(Administrator *ad_, QWidget *parent):
    ad(ad_), QListWidget(parent){
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setIconSize(QSize(114, 160));
    setUniformItemSizes(true);
    setResizeMode(QListWidget::Adjust);
    connect(this, &GuestListWidget::itemDoubleClicked, this, &GuestListWidget::itemdclicked);
}

Administrator* GuestListWidget::getAd(){return ad;}

void GuestListWidget::add_item(Guest *guest, int row){
    insertItem(row, new GuestItem(guest,this->getAd(), this));
}

void GuestListWidget::itemdclicked(QListWidgetItem *item){
    auto item_ = dynamic_cast<GuestItem*> (item);
    GuestMessageDialog* gdialog = new GuestMessageDialog(item_->getguest(), this);
    gdialog->show();
}

GuestItem::GuestItem(Guest *guest, Administrator *ad, QListWidget *parent):
    guest(guest), ad(ad), QListWidgetItem(parent){
    setUI();
}

void GuestItem::setUI(){
    this->setText(QString::fromStdString("用户名：" + guest->getUsername() + "\n"
                                          "用户ID：" + std::to_string(guest->getID()) + "\n"));
}

Guest* GuestItem::getguest(){return guest;}

Administrator* GuestItem::getAd(){return ad;}

void GuestDialog::push_modify(){
    modi = true;
    setUI();
}

GuestDialog::GuestDialog(Guest *guest, Administrator* ad, QWidget *parent):
    guest(guest), ad(ad), QDialog(parent){
    modi = false;
    setUI();
}

void GuestDialog::setUI(){
    if(!modi){
        layout = new QGridLayout;
        ID = new QLabel(QString::fromStdString("用户ID：" + guest->getID()));
        layout->addWidget(ID, 1, 1);
        Username = new QLabel(QString::fromStdString("用户名：" + guest->getUsername()));
        layout->addWidget(Username, 2, 1);
        Bbook = new QLabel(QString::fromStdString("已借阅/预约图书共" + std::to_string(guest->getbBook()) + "本"));
        layout->addWidget(Bbook, 3, 1);
        confirm = new QPushButton("确认");
        layout->addWidget(confirm, 7, 1);
        modify = new QPushButton("修改信息");
        layout->addWidget(modify, 7, 2);
        books = new BookListWidget(guest);
        layout->addWidget(books, 5, 1);
        this->setLayout(layout);
    }
    else{
        delete ID;
        delete Username;
        delete Bbook;
        delete confirm;
        delete modify;
        layout = new QGridLayout;
        if(*modiType == 1){
            setusername = new QLineEdit;
            setusername->setPlaceholderText("原用户名："+ QString::fromStdString(guest->getUsername()));
            layout->addWidget(setusername, 1, 1);
        }
        else{
            setpassword = new QLineEdit;
            setpassword->setPlaceholderText("输入修改后的密码");
            setpassword->setEchoMode(QLineEdit::Password);
            layout->addWidget(setpassword, 1, 1);
            confirmPassword = new QLineEdit;
            confirmPassword->setPlaceholderText("确认密码");
            confirmPassword->setEchoMode(QLineEdit::Password);
            layout->addWidget(confirmPassword, 2, 1);
        }

        layout->addWidget(confirm, 3, 2);
        this->setLayout(layout);
    }
}

void GuestDialog::push_confirm(){
    if(modi){
        if(*modiType == 1)
        ad->modifyGuest(guest, "Usrename", setusername->text());
        else{
            if(setpassword->text() == confirmPassword->text()){
                QString password =  QCryptographicHash::hash((passwordBegin + setpassword->text() + passwordEnd).toLocal8Bit(), QCryptographicHash::Sha1).toHex();
                ad->modifyGuest(guest, "Password", password);
            }
            else{
                QMessageBox error;
                error.information(this, "error", "两次输入密码不一致！", QMessageBox::Ok);
            }
        }
    }
    else{
        this->close();
    }
}

void GuestListWidget::slotBrowse(std::string type, std::string value){
    std::vector<Guest*> guests = ad->find_guest(type, value);
    for(int i=0; i<guests.size(); ++i){
        add_item(guests[i], i);
    }
}

DialogChooseType::DialogChooseType(int *moditype_):
    modiType(moditype_){
    layout = new QGridLayout;
    password = new QRadioButton("密码");
    username = new QRadioButton("用户名");
    layout->addWidget(password, 1, 1);
    layout->addWidget(username, 1, 2);
    settype = new QButtonGroup;
    settype->addButton(password, 0);
    settype->addButton(username, 1);
    commit = new QPushButton("确认");
    layout->addWidget(commit, 2, 1);
    this->setLayout(layout);
    QObject::connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));

}

void DialogChooseType::push_commit(){
    int k = settype->checkedId();
    modiType = &k;
}
