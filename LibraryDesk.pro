#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T18:13:55
#
#-------------------------------------------------
QT       += sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryDesk


TEMPLATE = app


SOURCES += main.cpp\
    core/Administrator.cpp \
    core/Book.cpp \
    core/Guest.cpp \
    core/Record.cpp \
    Dialog/AddBookDialog.cpp \
    Dialog/DeleteBookDialog.cpp \
    Dialog/DeleteGuestDialog.cpp \
    Dialog/GuestMessageDialog.cpp \
    Dialog/ModifypwDialog.cpp \
    Dialog/SearchBookDialog.cpp \
    Dialog/SearchGuestDialog.cpp \
    Dialog/SearchRecordDialog.cpp \
    Dialog/SignupAd.cpp \
    Dialog/SignupGuest.cpp \
    Dialog/WaitingRecordDialog.cpp \
    ListWidget/BookListwidget.cpp \
    ListWidget/GuestListwidget.cpp \
    ListWidget/RecordListwidget.cpp \
    Mysql/AdministratorMysql.cpp \
    Mysql/BookMysql.cpp \
    Mysql/GuestMysql.cpp \
    Mysql/Mysql.cpp \
    Mysql/RecordMysql.cpp \
    Mysql/To_doMysql.cpp \
    Window/AdMainwindow.cpp \
    Window/ErrorMessage.cpp \
    Window/GtMainwindow.cpp \
    Window/LoginWindow.cpp \
    core/User.cpp

HEADERS  += \
    core/Administrator.h \
    core/Book.h \
    core/constant.h \
    core/Guest.h \
    core/record.h \
    core/User.h \
    Dialog/AddBookDialog.h \
    Dialog/DeleteBookDialog.h \
    Dialog/DeleteGuestDialog.h \
    Dialog/GuestMessageDialog.h \
    Dialog/ModipwDialog.h \
    Dialog/SearchBookDialog.h \
    Dialog/SearchGuestDialog.h \
    Dialog/SearchRecordDialog.h \
    Dialog/SignupAd.h \
    Dialog/SignupGuest.h \
    Dialog/WaitingRecordDialog.h \
    ListWidget/BookListwidget.h \
    ListWidget/GuestListwidget.h \
    ListWidget/RecordListwidget.h \
    Mysql/AdministratorMysql.h \
    Mysql/BookMysql.h \
    Mysql/GuestMysql.h \
    Mysql/Mysql.h \
    Mysql/RecordMysql.h \
    Mysql/To_domysql.h \
    Window/AdMainwindow.h \
    Window/ErrorMessage.h \
    Window/GtMainwindow.h \
    Window/LoginWindow.h

FORMS    += mainwindow.ui \
    searchguest.ui
