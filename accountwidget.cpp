#include "accountwidget.h"
#include "ui_accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QWidget(parent), PdmRuntimeRef(),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    loginWidget = new LoginWidget();
    ui->gridLayout->addWidget(loginWidget);
}

AccountWidget::~AccountWidget()
{
    delete ui;
    delete loginWidget;
}
