#include "accountwidget.h"
#include "ui_accountwidget.h"

AccountWidget::AccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWidget)
{
    ui->setupUi(this);
}

AccountWidget::~AccountWidget()
{
    delete ui;
}
