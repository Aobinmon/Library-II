#ifndef GUESTLISTWIDGET_H
#define GUESTLISTWIDGET_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <string>
#include <QRadioButton>
#include <QButtonGroup>
#include "core/constant.h"
#include "core/Guest.h"
#include "core/Administrator.h"
#include "BookListwidget.h"
class GuestListWidget : public QListWidget{
    Q_OBJECT
private:
    Administrator* ad;
public:
    GuestListWidget(Administrator* ad_, QWidget* parent=0);
    void add_item(Guest* guest, int row);
    Administrator* getAd();
public slots:
    void slotBrowse(std::string type, std::string value);
    void itemdclicked(QListWidgetItem* item);
};

class GuestItem : public QListWidgetItem{
public:
    Guest* getguest();
    Administrator* getAd();
    GuestItem(Guest* guest, Administrator* ad, QListWidget* parent=0);
private:
    Guest* guest;
    Administrator* ad;
    void setUI();
};

class GuestDialog : public QDialog{
    Q_OBJECT
public:
    void setUI();
    GuestDialog(Guest* guest, Administrator* ad, QWidget* parent=0);
private:
    bool modi;
    int* modiType;
    Guest* guest;
    Administrator* ad;
    QGridLayout* layout;
    QPushButton *modify, *confirm;
    QLabel *ID, *Username, *Bbook;
    QLineEdit *setusername, *setpassword, *confirmPassword;
    BookListWidget* books;
private slots:
    void push_confirm();
    void push_modify();
};

class DialogChooseType : public QDialog{
    Q_OBJECT
    int *modiType;
public:
    DialogChooseType(int *moditype_);
    QGridLayout* layout;
    QRadioButton* password,* username;
    QButtonGroup *settype;
    QPushButton *commit;
public slots:
    void push_commit();
};

#endif // GUESTLISTWIDGET_H
