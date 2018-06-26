#ifndef SignupAd_H
#define SignupAd_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

class SignupAdDialog : public QWidget{
    Q_OBJECT
private:
    QLabel *username, *password1, *password2;
    QPushButton *submit;
    QLineEdit *setusername, *setpassword, *confirmpassword;
    QGridLayout* layout;
public:
    SignupAdDialog();
    ~SignupAdDialog();
private slots:
    void push();
};

#endif // AD_H
