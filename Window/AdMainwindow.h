#ifndef URDESKTOP_H
#define URDESKTOP_H
#include <QWidget>
#include <QToolBar>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QMainWindow>
#include "core/Administrator.h"
#include <QGridLayout>
#include "Dialog/WaitingRecordDialog.h"
#include "LoginWindow.h"
class AdMainWindow : public QMainWindow{
    Q_OBJECT
public:
    AdMainWindow(Administrator* ad_, QSqlDatabase& db);
    ~AdMainWindow(){}
private:
     QLabel* welcome;
     QAction *Reader_function[6], *Book_function[6], *Record_function, *addAdministrator, *modiPassword;
     QMenu* menu[4];
     QToolBar *toolbar;
     QMenuBar* total;
     Administrator* ad;
     Loginwindow* login;
    WaitingRecordDialog* to_do;
    QSqlDatabase& db;
    QPushButton* logout;
    void getToDo();
private slots:
    void add_guest();
    void delete_guest();
    void change_password();
    void search_record();
    void search_book();
    void add_book();
    void delete_book();
    void search_guest();
    void add_ad();
    void push_logout();
};
#endif // URDESKTOP_H
