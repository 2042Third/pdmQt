#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

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
  QWidget *activeWindow = QApplication::activeWindow();
  if (activeWindow) {
    QRect activeWindowGeometry = activeWindow->geometry();
    int x = activeWindowGeometry.x();
    int y = activeWindowGeometry.y();
    int width = activeWindowGeometry.width();
    int height = activeWindowGeometry.height();

    debugWindow->move(QPoint(x+width,y)); // Put the debug window to the right of the active window if possible.
    debugWindow->titleBar->changeName("Debug Messages");
  }
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

