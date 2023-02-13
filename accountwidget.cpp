#include "accountwidget.h"
#include "ui_accountwidget.h"
#include "loginwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    loginWidget = new LoginWidget(this);
    ui->gridLayout->addWidget(loginWidget);
}

AccountWidget::~AccountWidget()
{
    delete ui;
    delete loginWidget;
}
