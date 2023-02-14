#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debugWindow = new DebugWindow(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete debugWindow;
}


void MainWindow::on_actionSettings_triggered()
{
    if (!settingsWindow){
        settingsWindow = new SettingsMainWindow(ui->centralwidget);
        connect(settingsWindow,&SettingsMainWindow::log,debugWindow,&DebugWindow::appendMessage);
    }

    settingsWindow->show(); // Show the PDM settings window.
}


void MainWindow::on_actionAccount_triggered()
{
    if (!settingsWindow){
        settingsWindow = new SettingsMainWindow(ui->centralwidget);
        connect(settingsWindow,&SettingsMainWindow::log,debugWindow,&DebugWindow::appendMessage);
    }
    // Open the setting window and to the account page.
    settingsWindow->navToAccount();
    settingsWindow->show(); // Show the PDM settings window.
}


void MainWindow::on_actionDebug_Messages_triggered()
{
//    if(!debugWindow)
//        debugWindow = new DebugWindow(ui->centralwidget);
    debugWindow->show();
}

