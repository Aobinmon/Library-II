#ifndef MODIPASSWORDDIALOG
#define MODIPASSWORDDIALOG
#include <QDialog>
#include <QGridLayout>
#include "core/Administrator.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ModifyPasswordDialog : public QDialog{
    Q_OBJECT
private:
    QGridLayout* layout;
    QLabel* pw1, *pw2;
    QLineEdit *setpw, *confirmpw;
    QPushButton *commit;
    User* user;
public:
    ModifyPasswordDialog(User* user_);
private slots:
    void push_commit();
};




#endif
