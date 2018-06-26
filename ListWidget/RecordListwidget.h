#ifndef RECORDLISTWIDGET_H
#define RECORDLISTWIDGET_H
#include <QListWidget>
#include <QGridLayout>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include "core/Administrator.h"

class RecordListWidget : public QListWidget{
    Q_OBJECT
private:
    User *user;
public:
    RecordListWidget(User* user_, QWidget* parent=0);
    void add_item(Record* record, int row);
    User* getUser();
public slots:
    void slotBrowse(QString type_, QString value);
    void itemclicked(QListWidgetItem* item);
};

class RecordItem : public QListWidgetItem{
private:
    Record* record;
public:
    RecordItem(Record* record_, QListWidget* parent=0);
    Record* getRecord();
};

class RecordDialog : public QDialog{
    Q_OBJECT
private:
    Record* record;
    QPushButton *exit;
    QLabel *guest, *book, *type, *result;
    QGridLayout *layout;
public:
    RecordDialog(Record* record_);
};

#endif // RECORDLISTWIDGET_H
