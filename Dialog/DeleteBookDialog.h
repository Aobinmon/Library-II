#ifndef DELETEBOOKDIALOG
#define DELETEBOOKDIALOG
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include "core/Administrator.h"
class DeleteBookDialog : public QDialog{
    Q_OBJECT
private:
    QPushButton* commit, *exit;
    QGridLayout* layout;
    QLabel* notice;
    QLineEdit* getID;
    Administrator* ad;
public:
    DeleteBookDialog(Administrator* ad_);
private slots:
    void push_commit();
};


#endif
