
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
  ui->stackedWidget->addWidget(acc_ui);
  buttons.push_back(ui->settingAccountButton); // 0, account button

  // Set the focus to the "acc_ui" widget
  acc_ui->setFocus();
  // Make sure "acc_ui" is the current widget
  ui->stackedWidget->setCurrentWidget(acc_ui);

  info_ui = new InformationWidget(ui->centralwidget);
  info_ui->setObjectName("info_ui");
  ui->stackedWidget->addWidget(info_ui);
  buttons.push_back(ui->settingInfoButton); // 1, info button

  settings_ui = new settingsmenuWidget(ui->centralwidget);
  settings_ui->setObjectName("settings_ui");
  ui->stackedWidget->addWidget(settings_ui);
  buttons.push_back(ui->settingsSettingsButton); // 2, settings button

  ui->settingAccountButton->setText("");
  ui->settingAccountButton->setIcon(QIcon(":/images/icon/account"));
  ui->settingAccountButton->setIconSize(QSize(30, 30));
  ui->settingAccountButton->setToolTip("Account");
  ui->settingAccountButton->setMinimumHeight(50);
  ui->settingAccountButton->setMaximumHeight(50);
  ui->settingAccountButton->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");

  ui->settingInfoButton->setText("");
  ui->settingInfoButton->setIcon(QIcon(":/images/icon/information"));
  ui->settingInfoButton->setIconSize(QSize(30, 30));
  ui->settingInfoButton->setToolTip("Information");
  ui->settingInfoButton->setMinimumHeight(50);
  ui->settingInfoButton->setMaximumHeight(50);
  ui->settingInfoButton->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");

  ui->settingsSettingsButton->setText("");
  ui->settingsSettingsButton->setIcon(QIcon(":/images/icon/settings"));
  ui->settingsSettingsButton->setIconSize(QSize(30, 30));
  ui->settingsSettingsButton->setToolTip("Settings");
  ui->settingsSettingsButton->setMinimumHeight(50);
  ui->settingsSettingsButton->setMaximumHeight(50);
  ui->settingsSettingsButton->setStyleSheet("QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: lightgray; }");

  setActiveButton(0);
}

SettingsMainWindow::~SettingsMainWindow()
{
    delete ui;
    delete acc_ui;
    delete info_ui;
    delete settings_ui;
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

void SettingsMainWindow::on_settingsSettingsButton_released()
{
  ui->stackedWidget->setCurrentWidget(settings_ui);
  setActiveButton(2);
}

