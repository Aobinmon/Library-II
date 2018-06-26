#ifndef SEARCHGUEST_H
#define SEARCHGUEST_H
#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <string>
#include "Listwidget/GuestListwidget.h"

class SearchGuestDialog : public QDialog{
    Q_OBJECT
public:
    SearchGuestDialog(Administrator* ad, QWidget* parent=0);
private:
    QButtonGroup* setcolumn;
    QRadioButton* ID, *Username;
    QLineEdit* setvalue;
    QGridLayout* layout;
    QPushButton* commit, *browse;
    GuestListWidget* listwidget;
    Administrator* ad;
    void setUI();
public slots:
    void push_browse();
signals:
    void signalBrowse(std::string type, std::string value);
};

#endif // SEARCHGUEST_H
