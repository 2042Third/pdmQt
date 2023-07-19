#include "accountwidget.h"
#include "ui_accountwidget.h"
#include <QObject>

AccountWidget::AccountWidget(QWidget *parent, PdmRunTime* rtIn) :
  QWidget(parent), PdmRuntimeRef(rtIn)
  ,ui(new Ui::AccountWidget)
{
  ui->setupUi(this);
  loginWidget = new LoginWidget( this, rt);
  ui->gridLayout->addWidget(loginWidget);

  informationWidget = new UserInformation(this, rt); // Ready the user information widget for use.
  connect(rt, &PdmRunTime::loginSuccess, this, &AccountWidget::accountLoginSuccess);
  // If the login is already successful, change the widget to the user information widget.
  if (rt->isLoginSuccessful()) {
    accountLoginSuccess();
  }

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

  // Hide the login widget and display the user information widget.
  loginWidget->hide();
  ui->gridLayout->removeWidget(loginWidget);
  ui->gridLayout->addWidget(informationWidget);
  informationWidget->show();
  informationWidget->displayUserInfo();

}



