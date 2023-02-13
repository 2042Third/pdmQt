#include "settingsmainwindow.h"
#include "ui_settingsmainwindow.h"

SettingsMainWindow::SettingsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsMainWindow)
{
    ui->setupUi(this);
}

SettingsMainWindow::~SettingsMainWindow()
{
    delete ui;
}

void SettingsMainWindow::on_settingAccountButton_released()
{

}

