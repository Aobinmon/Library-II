#ifndef DELETEGUEST_H
#define DELETEGUEST_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "core/Administrator.h"
#include <QGridLayout>
class DeleteGuestDialog : public QDialog{
    Q_OBJECT
public:
    DeleteGuestDialog(Administrator* ad_, QWidget* parent = 0);
private:
    QLabel* id;
    QGridLayout* layout;
    Administrator* ad;
    QLineEdit *setid;
    QPushButton *commit;
private slots:
    void push_commit();
};

#endif // DeleteGuestDialog_H
