#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingsmainwindow.h"

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

