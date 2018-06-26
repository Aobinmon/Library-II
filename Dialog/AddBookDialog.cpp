#include "AddBookDialog.h"
#include <QMessageBox>
AddBookDialog::AddBookDialog(Administrator *ad_, QWidget *parent):
    QDialog(parent), ad(ad_){
    layout = new QGridLayout(this);
    bookname = new QLabel(tr("书名"), this);
    layout->addWidget(bookname, 1, 1);
    writer = new QLabel(tr("作者"), this);
    layout->addWidget(writer, 2, 1);
    press = new QLabel(tr("出版社"), this);
    layout->addWidget(press, 3, 1);
    presstime = new QLabel(tr("出版时间"), this);
    layout->addWidget(presstime, 4, 1);
    type = new QLabel(tr("类型"), this);
    layout->addWidget(type, 5, 1);
    position = new QLabel(tr("馆藏位置"), this);
    layout->addWidget(position, 6, 1);
    summary = new QLabel(tr("简介"), this);
    layout->addWidget(summary, 7, 1);

    setbookname = new QLineEdit(this);
    setbookname->setPlaceholderText(tr("请输入书名"));
    layout->addWidget(setbookname, 1, 2);
    setwriter = new QLineEdit(this);
    setwriter->setPlaceholderText(tr("请输入作者"));
    layout->addWidget(setwriter, 2, 2);
    setpress = new QLineEdit(this);
    setpress->setPlaceholderText("请输入出版社");
    layout->addWidget(setpress, 3, 2);
    setpresstime = new QLineEdit(this);
    setpresstime->setPlaceholderText("请输入出版时间");
    layout->addWidget(setpresstime, 4, 2);
    settype = new QLineEdit(this);
    settype->setPlaceholderText("请输入书籍类型");
    layout->addWidget(settype, 5, 2);
    setposition = new QLineEdit(this);
    setposition->setPlaceholderText("请输入馆藏位置");
    layout->addWidget(setposition, 6, 2);
    setsummary = new QTextEdit(this);
    setsummary->setPlaceholderText("请输入简介");
    layout->addWidget(setsummary, 8, 1);

    commit = new QPushButton("确认添加", this);
    layout->addWidget(commit, 8, 2);
    connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));
}

void AddBookDialog::push_commit(){
    int num, num1;
    std::vector<Book*> books = ad->findBook(QString::fromStdString("Bookname").toStdString(), setbookname->text().toStdString());
    num = books.size();
    ad->addBook(new Book(0, setbookname->text().toStdString(), setwriter->text().toStdString(), setposition->text().toStdString(),setpress->text().toStdString(),
                         setpresstime->text().toStdString(), settype->text().toStdString(), 1, setsummary->toPlainText().toStdString()));
    std::vector<Book*> books1 = ad->findBook(QString::fromStdString("Bookname").toStdString(), setbookname->text().toStdString());
    num1 = books1.size();
    if(num1 > num){
        QMessageBox::information(this, "congratulations", "添加成功", QMessageBox::Ok);
        this->close();
    }
    else QMessageBox::information(this, "error", "添加失败", QMessageBox::Ok);
}
