#ifndef WaitingRecordDialog_H
#define WaitingRecordDialog_H
#include "core/Administrator.h"
#include "core/record.h"
#include <vector>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
class WaitingRecordDialog : public QDialog{
    Q_OBJECT
    bool done;
    int now;
    std::vector<Record*> record;
    Record* recordnow;
    Administrator* ad;
    To_doMysql* tm;
    QPushButton*approve, *refuse;
    QLabel *book, *user, *type;
    QGridLayout *layout;
public:
    WaitingRecordDialog(Administrator* ad_, std::vector<Record*> record_, QWidget* parent=0);
private slots:
    void push_approve();
    void push_refuse();
private:
    void next();
};


#endif // WaitingRecordDialog_H
