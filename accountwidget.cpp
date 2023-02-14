#include "accountwidget.h"
#include "ui_accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
    loginWidget = new LoginWidget();
    ui->gridLayout->addWidget(loginWidget);
    emit log("Account widget Created","#00FF00");
    connect (loginWidget,&LoginWidget::log, this,&AccountWidget::log);
}

AccountWidget::~AccountWidget()
{
    delete ui;
    delete loginWidget;
}
