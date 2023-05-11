//
// Created by 18604 on 5/11/2023.
//

#ifndef PDM_QT_PASSWORDDIALOG_H
#define PDM_QT_PASSWORDDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "PdmRuntimeRef.h"

class PasswordDialog : public QDialog, public PdmRuntimeRef{
Q_OBJECT

public:

  PasswordDialog(QWidget *parent = nullptr) : QDialog(parent) , PdmRuntimeRef(){
    setWindowTitle("Enter Application Password");

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Enter Password:");
    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");

    layout->addWidget(label);
    layout->addWidget(m_passwordLineEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &PasswordDialog::checkPassword);
    connect(cancelButton, &QPushButton::clicked, this, &PasswordDialog::reject);
  }

  void setRef(PdmRunTime* rtRef) override {
    PdmRuntimeRef::setRef(rtRef);
  }

private slots:
  void checkPassword() {
    if (m_passwordLineEdit->text().size()>=4) {
      rt->wt.app_ps= m_passwordLineEdit->text().toStdString(); //set the local password.
      accept();
    } else {
      QMessageBox::warning(this, "Error", "App password too short, please try a length of greater than 4 characters next time."
                                          " Using your password as the app password.");
      rt->wt.app_ps = rt->wt.data;
      m_passwordLineEdit->clear();
    }
  }

private:
  QLineEdit *m_passwordLineEdit;
};



#endif //PDM_QT_PASSWORDDIALOG_H
