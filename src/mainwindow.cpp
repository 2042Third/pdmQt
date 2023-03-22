#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  debugWindow = new DebugWindow(ui->centralwidget);
  rt = new PdmRunTime();
  connect(rt, &PdmRunTime::log, debugWindow, &DebugWindow::appendMessage);
  connect(rt, &PdmRunTime::loginSuccess, this, &MainWindow::mainwindowLoginSuccess);
  statusBar()->showMessage("No Login"); rt->currentStatusBar = QString("No Login");
  statusBar()->setToolTip("Login to your account in Settings->Account.");

  // Restore the previous status bar message once the tooltip is hidden
  connect(qApp, &QGuiApplication::focusObjectChanged, [=](QObject *newFocusObject) {
    Q_UNUSED(newFocusObject);
    statusBar()->showMessage(rt->currentStatusBar);
  });

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

void MainWindow::mainwindowLoginSuccess() {
  if (rt->showUsernameInStatusBar) {
    statusBar()->showMessage(rt->wt.userinfo.username.c_str()); // Show username in status bar.
    rt->currentStatusBar = rt->wt.userinfo.username.c_str();
  }
  else {
    statusBar()->showMessage(""); // Hide warning message.
    rt->currentStatusBar = "";
  }
  statusBar()->setToolTip("");
  // Add button menu item "open user database location" to the help menu bar.
  QAction *openUserDatabaseLocation = new QAction("Open User Database Location", this);
  connect(openUserDatabaseLocation, &QAction::triggered, this, &MainWindow::open_user_database_location);
  ui->menuHelp->addAction(openUserDatabaseLocation);

}

void MainWindow::open_user_database_location() {
  QString filePath = rt->data_loc.c_str(); // Replace with the actual file path
  QFileInfo fileInfo(filePath);
  QDir dir = fileInfo.dir();

#ifdef Q_OS_WIN

  QString command = "explorer.exe";
  QStringList args;
  args << "/select," + QDir::toNativeSeparators(fileInfo.absoluteFilePath());
  emit rt->log(">>>Executing command: "+command+ " "+ args.join(" "), "#C22A1C");
  QProcess::startDetached(command, args);
#elif defined(Q_OS_MAC)
  QStringList scriptArgs;
  scriptArgs << QLatin1String("-e");
  scriptArgs << QString::fromLatin1("tell application \"Finder\" to reveal POSIX file \"%1\"")
                 .arg(fileInfo.absoluteFilePath());
  QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
  scriptArgs.clear();
  scriptArgs << QLatin1String("-e");
  scriptArgs << QLatin1String("tell application \"Finder\" to activate");
  QProcess::execute(QLatin1String("/usr/bin/osascript"), scriptArgs);
#else
    // Fallback to open the folder containing the file
    QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absolutePath()));
#endif
}

