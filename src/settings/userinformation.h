#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "PdmRunTimeRef.h"

namespace Ui {
class UserInformation;
}

class UserInformation : public QWidget, public PdmRunTimeRef
{
    Q_OBJECT

public:
  explicit UserInformation(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~UserInformation();
  void displayUserInfo();

private:
  Ui::UserInformation *ui;
  QLabel * usernameLabel;
  QLabel * emailLabel;
  QLabel * creationDateLabel;
  QLabel * usernameLineEdit;
  QLabel * emailLineEdit;
  QLabel * creationDateLineEdit;
  QVBoxLayout *layout;
};

#endif // USERINFORMATION_H
