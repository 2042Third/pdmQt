#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>

#include "loginwidget.h"
#include "PdmRuntimeRef.h"
#include "userinformation.h"

namespace Ui {
class AccountWidget;
}

class AccountWidget : public QWidget, public PdmRuntimeRef
{
  Q_OBJECT

public:
  explicit AccountWidget(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~AccountWidget();
  LoginWidget * loginWidget;
  UserInformation* informationWidget;

public slots:
  void accountLoginSuccess () ;
private:
  Ui::AccountWidget *ui;

};

#endif // ACCOUNTWIDGET_H
