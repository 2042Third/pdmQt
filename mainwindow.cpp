#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
// Read the contents of the .qss file into a string
//  QFile file("Geoo.qss");
//  QFile file("DeepBox.qss");
//  QFile file("Combinear.qss");
//  file.open(QFile::ReadOnly | QFile::Text);
//  QTextStream stream(&file);
//  QString stylesheet = stream.readAll();
//  file.close();

  // Apply the stylesheet to the main window
//  this->setStyleSheet(stylesheet);

  ui->setupUi(this);
  debugWindow = new DebugWindow(ui->centralwidget);
  rt = new PdmRunTime();
  connect(rt, &PdmRunTime::log, debugWindow, &DebugWindow::appendMessage);

}

MainWindow::~MainWindow()
{
  delete ui;
  delete debugWindow;
  delete rt;
}


void MainWindow::on_actionSettings_triggered()
{
  newSettingsWindow();
  settingsWindow->show(); // Show the PDM settings window.
}

void MainWindow::on_actionAccount_triggered()
{
  newSettingsWindow();
  // Open the setting window and to the account page.
  settingsWindow->navToAccount();
  settingsWindow->show(); // Show the PDM settings window.
}


// Signals

void MainWindow::on_actionDebug_Messages_triggered()
{
    debugWindow->show();
}

// Helpers

void MainWindow::newSettingsWindow() {
  if (!settingsWindow){
    settingsWindow = new SettingsMainWindow(ui->centralwidget);
    settingsWindow->setRef(rt);
  }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", "", "Text Files (*.txt);;All Files (*)");
        if (fileName.isEmpty()) {
            qDebug() << "No file was selected.";
            return;
        }

        QFileInfo fileInfo(fileName);
        qint64 fileSize = fileInfo.size();
        qDebug() << "Selected file:" << fileName;
        debugWindow->appendMessage("File Opened: ");
        debugWindow->appendMessage("  \""+fileName+"\"");
        debugWindow->appendMessage("  size="+QString::number(fileSize));
}

