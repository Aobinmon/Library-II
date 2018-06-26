#include "BookListwidget.h"
#include <QString>
#include <QMessageBox>
BookItem::BookItem(Book* book_, User* user_, QListWidget* parent):
    book(book_), user(user_),QListWidgetItem(parent){
    setUI();
}

void BookDialog::push_ok(){
    this->close();
}

BookDialog::BookDialog(Book* book_, User* user_):
    user(user_), book(book_){
    layout = new QGridLayout(this);
    name = new QLabel(QString::fromStdString("书名："+book->getBookName()));
    layout ->addWidget(name, 1, 1);
    type = new QLabel(QString::fromStdString("类型："+ book->getType()));
    layout->addWidget(type, 2, 2);
    id = new QLabel("ID:"+QString::number(book->getID()));
    layout->addWidget(id, 1, 2);
    writer = new QLabel(QString::fromStdString("作者："  + book->getWriterName()));
    layout->addWidget(writer, 2, 1);
    press = new QLabel(QString::fromStdString("出版社："+book->getPress()));
    layout->addWidget(press, 3, 1);
    presstime = new QLabel(QString::fromStdString("出版时间："+book->getPressTime()));
    layout->addWidget(presstime, 3, 2);
    position = new QLabel(QString::fromStdString("馆藏位置："+book->getPosition()));
    layout->addWidget(position, 4, 1);
    summary = new QTextEdit;
    summary->setText(QString::fromStdString(book->getSummary()));
    summary->setReadOnly(true);
    layout->addWidget(summary, 5, 1, 2, 2);
    onshelf = new QLabel;
    layout->addWidget(onshelf, 8, 1);
    if(book->getOnshelf() == 1) {
        onshelf->setText("在架");
        if(user->getType() == 0){
            borrow = new QPushButton("我要借阅", this);
            layout->addWidget(borrow, 9, 1);
            connect(borrow, SIGNAL(clicked(bool)), this, SLOT(push_borrow()));
        }
    }
    else{
        QString rtime;
        std::string btime = book->getborrowTime();
        int year=0;
        for(int i=0; i<4; ++i){
            year = year*10+(btime[i]-'0');
        }
        int month = (btime[5]-'0')*10+(btime[6]-'0');
        int day = (btime[8]-'0')*10+btime[9]-'0';
        if(month == 12){
            year += 1;
            rtime = QString::number(year) + "-01-" + QString::number(day);
        }
        else if(day == 31 && ((month<=7 && month%2==1) || (month>=8 && month%2 == 0))){
            day = 30;
            month += 1;
            rtime = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
        }
        else{
            month += 1;
            rtime = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
        }
        onshelf->setText("外借中   借阅日期：" + QString::fromStdString(btime)+"\n" +
                         "应归还日期：" + rtime);

        if(ifhold()){
            re = new QPushButton("我要归还", this);
            layout->addWidget(re, 9 ,1);
            connect(re, SIGNAL(clicked(bool)), this, SLOT(push_re()));
        }
        else if(ifapp()){
            appo = new QLabel("已被预约",this);
            layout->addWidget(appo, 8, 2);
        }
        else{
            app = new QPushButton("我要预约", this);
            layout->addWidget(app, 8, 2);
            connect(app, SIGNAL(clicked(bool)), this, SLOT(push_app()));
        }
    }
    if(user->getType() == 1){
        change = new QPushButton("修改信息", this);
        layout->addWidget(change, 9, 1);
        connect(change, SIGNAL(clicked(bool)), this, SLOT(push_change()));
    }
    ok = new QPushButton(tr("退出"), this);
    QObject::connect(ok, SIGNAL(clicked(bool)), this, SLOT(close()));
    layout->addWidget(ok, 9, 2);
    this->setLayout(layout);
}

void BookDialog::push_re(){
    Guest* guest = dynamic_cast<Guest*> (user);
    guest->ApplyreturnBook(book);
    QMessageBox::information(this, "congratulations", "成功申请归还", QMessageBox::Ok);
    this->close();
}

void BookDialog::push_borrow(){
    Guest* guest = dynamic_cast<Guest*> (user);
    if(guest->getbBook() + guest->getoBook() >= 3)
        QMessageBox::information(this, "error", "最多只能借阅/预约共三本书籍！", QMessageBox::Ok);
    else{
        guest->Applyforbook(book);
        QMessageBox::information(this, "congratualtions", "申请成功", QMessageBox::Ok);
        guest->increaseBbook();
    }
    this->close();
}

void BookDialog::push_app(){
    Guest* guest = dynamic_cast<Guest*> (user);
    if(guest->getbBook()+guest->getoBook() == 3){
        QMessageBox::information(this, "error", "最多只能借阅/预约共三本书籍！", QMessageBox::Ok);
    }
   else{
        guest->appointment(book);
        QMessageBox::information(this, "congratulations", "成功预约", QMessageBox::Ok);
        guest->increaseobook();
        this->close();
    }
}

void BookDialog::push_change(){
    setname = new QLineEdit;
    setname->setPlaceholderText(name->text());
    setwriter = new QLineEdit;
    setwriter->setPlaceholderText(writer->text());
    setpress = new QLineEdit;
    setpress->setPlaceholderText(press->text());
    setpresstime = new QLineEdit;
    setpresstime->setPlaceholderText(presstime->text());
    settype = new QLineEdit;
    settype->setPlaceholderText(type->text());
    setposition = new QLineEdit;
    setposition->setPlaceholderText(position->text());
    setonshelf = new QLineEdit;
    setonshelf->setPlaceholderText(name->text() + "(1--在架，0--外借)");
    delete name;
    delete writer;
    delete press;
    delete presstime;
    delete type;
    delete position;
    delete onshelf;
    layout->addWidget(setname, 1, 1);
    layout->addWidget(setwriter, 2, 1);
    layout->addWidget(setpress, 3, 1);
    layout->addWidget(setpresstime, 4, 1);
    layout->addWidget(settype, 5, 1);
    layout->addWidget(setposition, 6, 1);
    layout->addWidget(setonshelf, 7, 1);
    QPushButton* commit = new QPushButton("确认");
    layout->addWidget(commit, 8, 1);
    connect(commit, SIGNAL(clicked(bool)), this,  SLOT(push_commit()));
}

bool BookDialog::ifhold(){
    if(user->getType() == 0){
        Guest* guest = dynamic_cast<Guest*>(user);
        Book** books = guest->getbooks();
        for(int i=0; i<guest->getbBook(); ++i){
            if(books[i]->getID() == book->getID()) return true;
        }
        return false;
    }
}

bool BookDialog::ifapp(){
    qDebug() << "GuestID2 :" << book->getAppGuestID();
    if(book->getAppGuestID() == 0) return false;
    else return true;
}

void BookDialog::push_commit(){
    Administrator *ad = dynamic_cast<Administrator*>(user);
    if(setname->text().toStdString() != book->getBookName())
        ad->modifyBook(book, "Bookname", setname->text());
    if(setwriter->text().toStdString() != book->getWriterName())
        ad->modifyBook(book, "Writername", setwriter->text());
    if(setpress->text().toStdString() != book->getPress())
        ad->modifyBook(book, "Press", setpress->text());
    if(setpresstime->text().toStdString() != book->getPressTime())
        ad->modifyBook(book, "Presstime", setpresstime->text());
    if(settype->text().toStdString() != book->getType())
        ad->modifyBook(book, "Type", settype->text());
    if(setposition->text().toStdString() != book->getPosition())
        ad->modifyBook(book, "Position", setposition->text());
    if(setonshelf->text().toInt() != book->getOnshelf())
        ad->modifyBook(book, "Onshelf", setname->text());
}

void BookListWidget::add_Item(Book* book, int row){
    insertItem(row, new BookItem(book, user));
}

BookListWidget::BookListWidget(User* user, QWidget *parent):
    QListWidget(parent), user(user){
    setViewMode(QListView::IconMode);
    setMovement(QListView::Static);
    setIconSize(QSize(114, 160));
    setUniformItemSizes(true);
    setResizeMode(QListWidget::Adjust);
    connect(this, &BookListWidget::itemDoubleClicked, this, &BookListWidget::Clicked);
    row = 0;
}

void BookListWidget::Clicked(QListWidgetItem* item){
    auto *item_ = dynamic_cast<BookItem*>(item);
    BookDialog* bookdialog = new BookDialog(item_->getBook(), user);
    bookdialog->show();
}

void BookItem::setUI(){
    setText(QString::fromStdString(book->getBookName()+ '\n'
                                   + book->getWriterName() +'\n'
                                   + book->getPosition()));
}

void BookListWidget::getbook(std::string type, std::string feature){
    std::vector<Book*> books;
    Administrator* ad;
    Guest* guest;
    if(user->getType() == 1){
        ad = dynamic_cast<Administrator*> (user);
        books = ad->findBook(type ,feature);
    }
    else if(user->getType() == 0){
        guest = dynamic_cast<Guest*>(user);
        books = guest->findBook(type, feature);
    }
    int i;
    for(i=0; i<books.size(); ++i){
        add_Item(books[i], i+row);
    }
    row = i;
}
