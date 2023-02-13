#include "settingsmainwindow.h"
#include "ui_settingsmainwindow.h"
#include "accountwidget.h"
#include "informationwidget.h"

SettingsMainWindow::SettingsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsMainWindow)
{
    ui->setupUi(this);
}

bool SettingsMainWindow::destroyWidget(){
    QList< QWidget* > children;

    children = ui->gridLayout->findChildren< QWidget* >();
    for (unsigned int i=0; i<children.count();i++) {
        if (children.at( i )->objectName() == "widget") {
            delete children.at(i);
            return true;
        }
    }

    return false;
}

SettingsMainWindow::~SettingsMainWindow()
{
    delete ui;
}

void SettingsMainWindow::on_settingAccountButton_released()
{

    emit log("Clicked Account button in settings","#000000");
    acc_ui = new AccountWidget(ui->centralwidget);
    acc_ui->setObjectName("widget");
    if(lastWidget!=nullptr){
        ui->gridLayout->removeWidget(lastWidget);
        delete lastWidget;
    }
    ui->gridLayout->addWidget(acc_ui,2,1,1,3);
    lastWidget = acc_ui;

}


void SettingsMainWindow::on_widget_customContextMenuRequested(const QPoint &pos)
{

}


void SettingsMainWindow::on_settingInfoButton_released()
{
    emit log("Clicked Information button in settings","#000000");
    info_ui = new InformationWidget(ui->centralwidget);
    info_ui -> setObjectName("widget");

    if(lastWidget!=nullptr){
        ui->gridLayout->removeWidget(lastWidget);
        delete lastWidget;
    }
    ui->gridLayout->addWidget(info_ui,2,1,1,3);
    lastWidget = info_ui;
}

