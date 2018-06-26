#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
class ErrorMessage : public QMessageBox{
    Q_OBJECT
public:
    ErrorMessage(int type);
    ~ErrorMessage(){}
};
#endif // ERRORDIALOG_H
