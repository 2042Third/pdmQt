#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./pdmsettingswindow.h"

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
    static PdmSettingsWindow w;
    w.show(); // Show the PDM settings window.
}

