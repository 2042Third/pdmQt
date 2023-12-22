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
#include "PdmRunTimeRef.h"
#include "misc/md5.h"
#include "empp.h"

class PasswordDialog : public QDialog, public PdmRunTimeRef{
Q_OBJECT

public:

  explicit PasswordDialog(QWidget *parent = nullptr, PdmRunTime*rtIn= nullptr)
  : QDialog(parent) , PdmRunTimeRef(rtIn){
    setWindowTitle(mTitle);

    auto *layout = new QVBoxLayout(this);
    label = new QLabel(mLabel);
    m_passwordLineEdit = new QLineEdit;
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    auto *okButton = new QPushButton(mOkButton);
    auto *cancelButton = new QPushButton(mCancelButton);

    layout->addWidget(label);
    layout->addWidget(m_passwordLineEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &PasswordDialog::checkPassword);
    connect(cancelButton, &QPushButton::clicked, this, &PasswordDialog::reject);
  }


  void setLabel(const QString& str){
    label->setText(str);
  }



  /**
   * Sets whether or not to check a password input.
   * If check password, "ver" is decrypted using the input password and compared to "verComp".
   * If they are the same, then the password is correct.
   * @param b 1 if check password, 0 if not.
   * @param str the encrypted string to check.
   * @param plain the decrypted string to check.
   * @requires str not empty, plain not empty.
   * */
  void setMD5Verification(int b, std::string str, std::string plain){
    needVer=b;
    ver = str;
    verComp=plain;
  }

  int verification (const QString& ps){
    if (!needVer) return 1;
    if (needVer){
      emit rt->log("input pass: "+ps,"#016C05");
//      MD5 md5; md5.add(verComp.c_str(),verComp.size());
//      std::string verStr = md5.getHash();
      std::string verOut= loader_out(ps.toStdString(),ver);
      emit rt->log("verOut: "+QString::fromStdString(verOut),"#016C05");
      emit rt->log("verComp: "+QString::fromStdString(verComp),"#016C05");
      if (verOut==verComp) return 1;
      else return 0;
    }
    return 0;
  }

  // strings that contain the default messages
  QString mTitle = "Application Password";
  QString mLabel = "Set a Password:";
  QString mOkButton = "OK";
  QString mCancelButton = "Cancel";

private slots:
  void checkPassword() {
    if (m_passwordLineEdit->text().size()>=4 && verification(m_passwordLineEdit->text())) {
      rt->wt.app_ps= m_passwordLineEdit->text().toStdString(); //set the local password.
      accept();
    } else {
      QMessageBox::warning(this, "Error", "App password wrong."
                                          " Using your password as the app password.");
      rt->wt.app_ps = rt->wt.data;
      m_passwordLineEdit->clear();
    }
  }


private:
  QLineEdit *m_passwordLineEdit;
  QLabel *label;
  int needVer=0;
  std::string ver;
  std::string verComp;
};



#endif //PDM_QT_PASSWORDDIALOG_H
