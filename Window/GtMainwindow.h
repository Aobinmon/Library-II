#ifndef GTMAINWINDOW_H
#define GTMAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "LoginWindow.h"
#include "core/Guest.h"
#include "Listwidget/BookListwidget.h"
#include "Dialog/SearchBookDialog.h"
class GtMainWindow : public QMainWindow{
    Q_OBJECT
    QLabel* welcome;
    QAction* function[6];
    QMenu* bookmenu, *guestmenu;
    QMenuBar* menubar;
    Guest* guest;
    QPushButton* logout;
    Loginwindow* login;
    QSqlDatabase& db;
public:
    GtMainWindow(Guest* guest_,QSqlDatabase& db, QWidget* parent=0);
private slots:
    void search_book();
    void getMyRecord();
    void getMyMessage();
    void push_logout();
};

#endif // GTMAINWINDOW_H
