#include "informationwidget.h"
#include "ui_informationwidget.h"

InformationWidget::InformationWidget(QWidget *parent, PdmRunTime* rtIn) :
    QWidget(parent), PdmRunTimeRef(rtIn),
    ui(new Ui::InformationWidget)
{
    ui->setupUi(this);
}

InformationWidget::~InformationWidget()
{
    delete ui;
}
