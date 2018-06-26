#ifndef GTDIALOG_H
#define GTDIALOG_H
#include "core/Guest.h"
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "Listwidget/BookListwidget.h"
#include "core/record.h"
#include <QGridLayout>
class GuestMessageDialog : public QDialog{
    Q_OBJECT
private:
    QGridLayout* layout;
    Guest* guest;
    QPushButton *exit, *modify, *commit;
    BookListWidget* books1, *books2;
    QLabel* label1, *label2, *ID_, *Username_;
    QLineEdit *setun, *setpw, *confirmpw;
public:
    GuestMessageDialog(Guest* guest_, QWidget* parent);
    void setUI();
private slots:
    void push_modify();
    void push_commit();
};

#endif // GTDIALOG_H
