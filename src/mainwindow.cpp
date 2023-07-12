#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "handler/pdmqt/pdm_qt_net.h"
#include "notesView/NotesScroll.h"
#include "handler/pdm_qt_helpers.h"
#include "notesView/pdmListView.h"
#include "notesView/NoteEdit.h"
#include "notesView/NotesScrollDelegate.h"
#include <QObject>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>
#include <QListView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->tabWidget->setTabsClosable(true);
  debugWindow = new DebugWindow(ui->centralwidget);
  rt = new PdmRunTime();
  rt->main_window = this;
  connect(rt, &PdmRunTime::log, debugWindow, &DebugWindow::appendMessage);
  connect(rt, &PdmRunTime::loginSuccess, this, &MainWindow::mainwindowLoginSuccess);
  connect(rt, &PdmRunTime::noteHeadsSuccess, this, &MainWindow::mainwindowNoteHeadsSuccess);
  connect(rt, &PdmRunTime::noteListLeftClicked, this, &MainWindow::mainwindowNoteListLeftClicked);
  connect(rt, &PdmRunTime::noteRetrieveSuccess, this, &MainWindow::mainwindowNoteRetrieveSuccess);
  connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::mainwindowTabCloseRequested);

  //Default Messages
  statusBar()->showMessage("No Login"); rt->currentStatusBar = QString("No Login");
  statusBar()->setToolTip("Login to your account in Settings->Account.");

  // Setup noteListWidget
  NotesScrollDelegate *delegate = new NotesScrollDelegate(ui->notesListTab);
  rt->noteList = new NotesScroll(ui->notesListTab);
  auto *view = new pdmListView;
  view->setRef(rt);
  view->setModel(rt->noteList);
  view->setItemDelegate(delegate);
  auto *layout = new QVBoxLayout;
  layout->addWidget(view);

  ui->notesListTab->setLayout(layout);
  ui->notesListTab->show();

  // Restore the previous status bar message once the tooltip is hidden
  connect(qApp, &QGuiApplication::focusObjectChanged, [=](QObject *newFocusObject) {
    Q_UNUSED(newFocusObject);
    statusBar()->showMessage(rt->currentStatusBar);
  });

  // Finish settings up the settings
  rt->setup_settings();

  //Default geometry for the main window
  QWidget tempWidget;
  tempWidget.setGeometry(847, 236, defaultWidth, 905);

  QSettings settings;
  // Restore the previous window geometry
  restoreGeometry(settings.value("mainwindow/geometry",tempWidget.saveGeometry()).toByteArray());

  moveTimer = new PdmUpdateTimer(3000,this);
  resizeTimer = new PdmUpdateTimer(3000,this);
  connect(moveTimer, &PdmUpdateTimer::timeout, this, &MainWindow::onMoveTimerTimeout);
  connect(resizeTimer, &PdmUpdateTimer::timeout, this, &MainWindow::onResizeTimerTimeout);

  // Set the initial position of the splitter's handle
  QList<int> initialSizes;
  initialSizes << defaultWidth/5*2 << defaultWidth-defaultWidth/5*2;
  ui->splitter->setSizes(initialSizes);

  // Restore previous sessions' windows opened and their geometry
  QTimer::singleShot(0, [this]() { debugWindow->checkAndShow(); });
  // Check existing user, if exist ask for decryption password
  QTimer::singleShot(0, rt, &PdmRunTime::checkExistingUser);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete debugWindow;
  delete rt;
  delete moveTimer;
  delete resizeTimer;
//  delete rt->noteList;
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
//  debugWindow->setFocus();
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

  // Get notes heads calls.
  PDM::pdm_qt_net::client_action_note_heads(rt);
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


void MainWindow::moveEvent(QMoveEvent *event) {
  QMainWindow::moveEvent(event);
  // Start the timer when the window is moved
  moveTimer->start();
}
void MainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  // Start the timer when the window is resized
  resizeTimer->start();
}

void MainWindow::onMoveTimerTimeout() {
  emit rt->log("Window stopped moving: ", "#C22A1C");
  emit rt->log("  Final position: " + QString::number(this->x()) + ", " + QString::number(this->y()), "#C22A1C");
  QSettings settings;
  settings.setValue("mainwindow/geometry", saveGeometry());

}

void MainWindow::onResizeTimerTimeout() {
  emit rt->log("Window stopped resizing: ", "#C22A1C");
  emit rt->log("  Final size: " + QString::number(this->width()) + ", " + QString::number(this->height()), "#C22A1C");
  QSettings settings;
  settings.setValue("mainwindow/geometry", saveGeometry());
}

void MainWindow::mainwindowNoteHeadsSuccess() {
  emit rt->log("Note heads received.", "#C22A1C");
  if(rt->user_data->addAllToNoteList(rt->wt.data,rt->wt.userinfo.email, rt->noteList))
    emit rt->log("Note heads added to note list.", "#1CC22A");
  else emit rt->log("Error adding note heads to note list.", "#C22A1C");
}

void MainWindow::mainwindowNoteListLeftClicked(const QModelIndex &index) {
  emit rt->log("Note list left clicked: " + QString::number(index.row()), "#C22A1C");
  PDM::pdm_qt_net::client_action_note_retrieve(rt, stoi(rt->noteList->getNote(index)->note_id)); // Get the note from the server
}


void MainWindow::mainwindowNoteRetrieveSuccess(int noteId) {
  emit rt->log("Note open/retrieve received.", "#C22A1C");
  PDM::NoteMsg note ;
  rt->user_data->getNote(noteId,rt->wt.data, &note);
  if(noteEditMap.contains(note.note_id)) { // Check if this already exists in the tab widget.
    ui->tabWidget->setCurrentIndex(noteEditMap[note.note_id]->idx);
    noteEditMap[note.note_id]->setFocus();
    return;
  }
  auto * noteEdit= new NoteEdit(note);
  noteEditMap.insert(note.note_id, noteEdit); // Add to the map
  noteEdit->setRef(rt);
  noteEdit->setNote();
  int tabIndex = ui->tabWidget->addTab( noteEdit, noteEdit->getNote()->head.c_str());
  ui->tabWidget->setCurrentIndex(tabIndex);
  noteEdit->idx=tabIndex;
  noteEdit->setFocus();
}

void MainWindow::mainwindowTabCloseRequested(int index){
  emit rt->log("Tab close requested: " + QString::number(index), "#C22A1C");
  QWidget *widget = ui->tabWidget->widget(index);
  ui->tabWidget->removeTab(index);
  delete widget;
}

void MainWindow::on_actionZoom_In_triggered()
{
  emit rt->onZoomIn();
}


void MainWindow::on_actionZoom_Out_triggered()
{
  emit rt->onZoomOut();
}

