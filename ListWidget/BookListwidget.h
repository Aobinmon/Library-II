#ifndef BOOKLISTWIDGET_H
#define BOOKLISTWIDGET_H
#include <QlistWidget>
#include <QDialog>
#include <QListWidgetItem>
#include "core/Book.h"
#include "core/Administrator.h"
#include "core/Guest.h"
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
class BookItem: public QListWidgetItem{
    Book* book;
    User* user;
public:
    BookItem(Book* book_, User* user, QListWidget* parent=0);
    Book* getBook(){return book;}
    void setUI();
};

class BookListWidget : public QListWidget{
    Q_OBJECT
private:
    User* user;
    int row;
public:
    BookListWidget(User* user, QWidget* parent=0);
    void add_Item(Book* book, int row);
public slots:
    void Clicked(QListWidgetItem* item);
    void getbook(std::string type, std::string feature);
};

class BookDialog : public QDialog{
    Q_OBJECT
private:
    User* user;
    Book* book;
    QLabel *name,*id, *writer, *press, *presstime, *type, *position, *onshelf, *appo;
    QLineEdit  *setname, *setwriter, *setpress, *setpresstime, *settype, *setposition, *setonshelf;
    QTextEdit *setsummary;
    QTextEdit* summary;
    QGridLayout *layout;
    QPushButton *ok, *borrow, *change, *re, *app;
    bool ifhold();
    bool ifapp();
public :
    BookDialog(Book* book_, User* user_);
public slots:
    void push_ok();
    void push_borrow();
    void push_commit();
    void push_change();
    void push_app();
    void push_re();
};

#endif // BOOKLISTWIDGET_H
