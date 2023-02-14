#include "settingsmainwindow.h"
#include "ui_settingsmainwindow.h"
#include "accountwidget.h"
#include "informationwidget.h"

SettingsMainWindow::SettingsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsMainWindow)
{
    ui->setupUi(this);

  acc_ui = new AccountWidget(ui->centralwidget);
  acc_ui->setObjectName("acc_ui");
  info_ui = new InformationWidget(ui->centralwidget);
  info_ui->setObjectName("info_ui");
  ui->stackedWidget->addWidget(acc_ui);
  ui->stackedWidget->addWidget(info_ui);
}

SettingsMainWindow::~SettingsMainWindow()
{
    delete ui;
    delete acc_ui;
    delete info_ui;
}

void SettingsMainWindow::on_settingAccountButton_released()
{
  emit log("Clicked Account button in settings","#000000");
//  if (!acc_ui){
//    acc_ui = new AccountWidget(ui->centralwidget);
//    acc_ui->setObjectName("acc_ui");
//  }
//  ui->gridLayout->addWidget(acc_ui, 2, 1, 1, 3);
  ui->stackedWidget->setCurrentWidget(acc_ui);
}




void SettingsMainWindow::on_settingInfoButton_released()
{
  emit log("Clicked Information button in settings","#000000");
//  if (!info_ui){
//    info_ui = new InformationWidget(ui->centralwidget);
//    info_ui->setObjectName("info_ui");
//  }
//  ui->gridLayout->addWidget(info_ui, 2, 1, 1, 3);
  ui->stackedWidget->setCurrentWidget(info_ui);
}

