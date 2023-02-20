
#include "settingsmainwindow.h"
#include "ui_settingsmainwindow.h"

#include <QObject>


SettingsMainWindow::SettingsMainWindow(QWidget *parent) :
    QMainWindow(parent), PdmRuntimeRef(),
    ui(new Ui::SettingsMainWindow)
{
  ui->setupUi(this); // .ui file generated header setup

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
  emit rt->log("Clicked Account button in settings","#000000");
  ui->stackedWidget->setCurrentWidget(acc_ui);
}

void SettingsMainWindow::on_settingInfoButton_released()
{
  emit rt->log("Clicked Information button in settings","#000000");
  ui->stackedWidget->setCurrentWidget(info_ui);
}


