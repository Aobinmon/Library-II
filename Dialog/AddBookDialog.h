#ifndef AddBookDialogDialog_H
#define AddBookDialog_H
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialog>
#include "core/Administrator.h"
#include <QPushButton>
#include <QGridLayout>
class AddBookDialog : public QDialog{
    Q_OBJECT
public:
    AddBookDialog(Administrator *ad_, QWidget *parent=0);
private:
    Administrator *ad;
    QLabel *bookname, *writer, *press, *presstime, *type, *summary, *position;
    QLineEdit *setbookname,*settype, *setwriter, *setpress, *setpresstime, *setposition;
    QTextEdit *setsummary;
    QPushButton *commit;
    QGridLayout *layout;
private slots:
    void push_commit();
};

#endif
