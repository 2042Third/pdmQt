#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingsmainwindow.h"
#include "accountwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSettings_triggered()
{
    static SettingsMainWindow w;
    w.show(); // Show the PDM settings window.
}


void MainWindow::on_actionAccount_triggered()
{
    // Open the setting window and to the account page.
}

