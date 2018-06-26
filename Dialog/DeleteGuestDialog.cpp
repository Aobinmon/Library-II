#include "DeleteGuestDialog.h"
#include <QMessageBox>

DeleteGuestDialog::DeleteGuestDialog(Administrator* ad_, QWidget *parent):
    QDialog(parent), ad(ad_){
    id = new QLabel(tr("请输入需要删除的读者ID"), this);
    setid = new QLineEdit(this);
    setid->setPlaceholderText("读者ID");
    commit = new QPushButton(tr("确定"));
    QObject::connect(commit, SIGNAL(clicked(bool)), this, SLOT(push_commit()));
    layout = new QGridLayout;
    layout->addWidget(id, 1, 1);
    layout->addWidget(setid, 2, 1);
    layout->addWidget(commit, 3, 1);
    this->setLayout(layout);
}

void DeleteGuestDialog::push_commit(){
    if(!(ad->find_guest("ID", setid->text().toStdString()).empty())){
        Guest* guest = ad->find_guest("ID", setid->text().toStdString()).front();
        ad->deleteGuest(guest);
        if(ad->find_guest("ID", setid->text().toStdString()).empty()){
            QMessageBox box;
            box.information(this, tr("congratulation"), tr("成功删除"), QMessageBox::Ok);
            box.show();
            this->close();
        }
   }
    else{
        QMessageBox error;
        error.information(this, tr("ERROR!"), tr("不存在该读者"), QMessageBox::Ok);
        error.show();
    }
}
