#include "informationwidget.h"
#include "ui_informationwidget.h"

InformationWidget::InformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InformationWidget)
{
    ui->setupUi(this);
}

InformationWidget::~InformationWidget()
{
    delete ui;
}
