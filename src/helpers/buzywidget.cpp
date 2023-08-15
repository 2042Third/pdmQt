#include "buzywidget.h"
#include "ui_buzywidget.h"

BuzyWidget::BuzyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuzyWidget)
{
    ui->setupUi(this);
}

BuzyWidget::~BuzyWidget()
{
    delete ui;
}
