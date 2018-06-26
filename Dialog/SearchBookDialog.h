#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "core/Administrator.h"
#include "core/Guest.h"
#include "Listwidget/BookListwidget.h"
#include <map>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
class SearchBookDialog : public QDialog{
    Q_OBJECT
public:
    SearchBookDialog(User* user_, QWidget* parent=0);
private:
    QButtonGroup* setcolumn;
    QRadioButton *id, *bookname, *writername, *press, *presstime, *type;
    User* user;
    QPushButton* browse, *commit;
    QLineEdit* browser;
    QGridLayout* layout;
    std::map<int, QString> column;
    BookListWidget* listwidget;
signals:
    void signalBrowse(std::string type, std::string feature);
private slots:
    void push_browse();
};

#endif // SEARCHBOOK_H
