#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>

#include "loginwidget.h"
#include "PdmRuntimeRef.h"

namespace Ui {
class AccountWidget;
}

class AccountWidget : public QWidget, public PdmRuntimeRef
{
    Q_OBJECT

public:
  explicit AccountWidget(QWidget *parent = nullptr);
  ~AccountWidget();
  LoginWidget * loginWidget;
  void setRef(PdmRunTime* rtRef) override {
    PdmRuntimeRef::setRef(rtRef);
    loginWidget->setRef(rtRef);
    emit rtRef->log("Account widget Created","#00FF00");
  }
private:
    Ui::AccountWidget *ui;
};

#endif // ACCOUNTWIDGET_H
