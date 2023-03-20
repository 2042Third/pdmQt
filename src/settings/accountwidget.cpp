#include "accountwidget.h"
#include "ui_accountwidget.h"
#include <QObject>

AccountWidget::AccountWidget(QWidget *parent) :
  QWidget(parent), PdmRuntimeRef(),
  ui(new Ui::AccountWidget)
{
  ui->setupUi(this);
  loginWidget = new LoginWidget();
  ui->gridLayout->addWidget(loginWidget);

  informationWidget = new UserInformation(); // Ready the user information widget for use.

}

void AccountWidget::setRef(PdmRunTime *rtRef) {
  PdmRuntimeRef::setRef(rtRef);
  loginWidget->setRef(rtRef);
  informationWidget->setRef(rtRef);

  connect(rt, &PdmRunTime::loginSuccess, this, &AccountWidget::accountLoginSuccess);
  emit rtRef->log("Account widget Created","#00FF00");
}

AccountWidget::~AccountWidget()
{
  delete ui;
  delete loginWidget;
  delete informationWidget;
}

/**
 * Display account information if login successful.
 * Remove login widget and replace with another
 * */
void AccountWidget::accountLoginSuccess() {
  // Decrypt the user's data and store it in the runtime.
  rt->userDataCheck();
  // Hide the login widget and display the user information widget.
  loginWidget->hide();
  ui->gridLayout->removeWidget(loginWidget);
  ui->gridLayout->addWidget(informationWidget);
  informationWidget->show();
  informationWidget->displayUserInfo();

}



