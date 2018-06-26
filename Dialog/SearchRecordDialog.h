#ifndef SEARCHRECORD_H
#define SEARCHRECORD_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include "core/Administrator.h"
#include "Listwidget/RecordListwidget.h"
class SearchRecordDialog : public QDialog{
    Q_OBJECT
private:
    User* user;
    QGridLayout* layout;
    QPushButton *browse, *exit;
    QLabel *column, *note;
    std::map<int, QString> c;
    QLineEdit *setvalue;
    RecordListWidget* listwidget;
    QRadioButton *setc[6];
    QButtonGroup *setcolumn;
public:
    SearchRecordDialog(User* user_, QWidget* parent=0);
public slots:
    void push_browse();
signals:
    void signalBrowse(QString type_, QString value_);
};


#endif // SEARCHRECORD_H
