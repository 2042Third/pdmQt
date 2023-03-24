
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

  buttons.push_back(ui->settingAccountButton); // 0, account button
  buttons.push_back(ui->settingInfoButton); // 1, info button

  ui->settingAccountButton->setText("");
  ui->settingAccountButton->setIcon(QIcon(":/images/icon/account"));
  ui->settingAccountButton->setToolTip("Account");
//  ui->settingAccountButton->setFlat(true);
  ui->settingAccountButton->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");

  ui->settingInfoButton->setText("");
  ui->settingInfoButton->setIcon(QIcon(":/images/icon/information"));
  ui->settingInfoButton->setToolTip("Information");
//  ui->settingInfoButton->setFlat(true);
  ui->settingInfoButton->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");
  setActiveButton(0);
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
  setActiveButton(0);
}

void SettingsMainWindow::on_settingInfoButton_released()
{
  emit rt->log("Clicked Information button in settings","#000000");
  ui->stackedWidget->setCurrentWidget(info_ui);
  setActiveButton(1);
}

void SettingsMainWindow::setActiveButton(int idx) {
  for (int i = 0; i < buttons.size(); i++) {
    if (i == idx) {
      buttons[i]->setStyleSheet("QPushButton { background-color: lightblue; border: none; } QPushButton:hover { background-color: lightblue; }");
    } else {
      buttons[i]->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");
    }
  }
}


