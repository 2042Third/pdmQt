#include "mainwindow.h"
#include "mainwindowui.h"
#include "handler/pdmqt/pdm_qt_net.h"
#include "notesView/NotesScroll.h"
#include "notesView/pdmListView.h"
#include "notesView/NoteEdit.h"
#include "helpers/FlashingCircle.h"
#include "helpers/Animated.h"
#include <QObject>
#include <QMenu>
#include <QFileDialog>
#include <QProcess>
#include <QSettings>
#include <QListView>
#include <QWidgetAction>

#ifdef PDM_USE_FRAMELESSHELPER
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#endif // PDM_USE_FRAMELESSHELPER
MainWindow::MainWindow(QWidget *parent)
#ifdef PDM_USE_FRAMELESSHELPER
  : QMainWindow(parent,Qt::FramelessWindowHint)
#else
  : QMainWindow(parent)
#endif
    , ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->tabWidget->setTabsClosable(true);
  rt = new PdmRunTime();
  debugWindow = new DebugWindow(nullptr, rt);
  rt->main_window = this;
  connect(rt, &PdmRunTime::log, debugWindow, &DebugWindow::appendMessage);
  connect(rt, &PdmRunTime::logc, debugWindow, &DebugWindow::appendMessageC);
  connect(rt, &PdmRunTime::log_std, debugWindow, &DebugWindow::appendMessage_std);
  connect(rt, &PdmRunTime::logc_std, debugWindow, &DebugWindow::appendMessageC_std);
  connect(rt, &PdmRunTime::loginSuccess, this, &MainWindow::mainwindowLoginSuccess);
  connect(rt, &PdmRunTime::noteHeadsSuccess, this, &MainWindow::mainwindowNoteHeadsSuccess);
  connect(rt, &PdmRunTime::noteListLeftClicked, this, &MainWindow::mainwindowNoteListLeftClicked);
  connect(rt, &PdmRunTime::noteListRightClicked, this, &MainWindow::mainwindowNoteListRightClicked);
  connect(rt, &PdmRunTime::noteRetrieveSuccess, this, &MainWindow::mainwindowNoteRetrieveSuccess);
  connect(rt, &PdmRunTime::noteUpdateSuccess, this, &MainWindow::mainwindowNoteUpdateSuccess);
  connect(rt, &PdmRunTime::noteCreateSuccess, this, &MainWindow::mainwindowNoteCreateSuccess);
  connect(rt, &PdmRunTime::noteRename, this, &MainWindow::mainwindowNoteRename);

  connect(rt->statusQt, &StatusQt::statusChanged, this, &MainWindow::mainwindowRuntimeStatusChanged);
  connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::mainwindowTabCloseRequested);

  connect(ui->menubar, &QObject::destroyed, []() {
    qDebug() << "MenuBar was destroyed!";
  });

  //Default Messages
  statusBar()->showMessage("No Login"); rt->currentStatusBar = QString("No Login");
  statusBar()->setToolTip("Login to your account in Settings->Account.");

  // Setup noteListWidget
  rt->noteList = new NotesScroll(ui->notesListTab, rt); // This NEEDS to be created before the pdmListView for proxy model to work
  notesListView = new pdmListView(this, rt);
  notesListView->setModel(rt->noteList);
  auto *notelistlayout = new QVBoxLayout;
  auto *noteListActionLayout = new QHBoxLayout;
  auto *newNoteButton = new QPushButton("New Note", this);// Add the new note button
  sortingMenu = new pdmListSortingMenu(this, rt);
  connect(newNoteButton, &QPushButton::clicked, [=]() {
    rt->runCmd("note_new_note");
  });
  auto *refreshButton = new QPushButton("Refresh", this);// Add refresh button
  connect(refreshButton, &QPushButton::clicked, [=]() {
    rt->runCmd("note_refresh_list");
  });
  auto *sortingOptionButtom = new QPushButton("Sort", this);// Add refresh button
  connect(sortingOptionButtom, &QPushButton::clicked, [=]() {
    sortingMenu->displaySortingMenu(sortingOptionButtom->mapToGlobal(QPoint(0, sortingOptionButtom->height())));
    emit rt->logc("Opened Sorting Options Menu.", "blue");
  });
  noteListActionLayout->addWidget(refreshButton);
  noteListActionLayout->addWidget(newNoteButton);
  noteListActionLayout->addWidget(sortingOptionButtom);
  notelistlayout->addLayout(noteListActionLayout);
  notelistlayout->addWidget(notesListView);
  ui->notesListTab->setLayout(notelistlayout);
  ui->notesListTab->show();
  connect(rt->noteList, &NotesScroll::noteAdded, this, &MainWindow::onNoteAdded); // Connect the noteAdded signal to the onNoteAdded slot



  // Restore the previous status bar message once the tooltip is hidden
  connect(qApp, &QGuiApplication::focusObjectChanged, [=](QObject *newFocusObject) {
    Q_UNUSED(newFocusObject);
    if(!rt->isClosing) statusBar()->showMessage(rt->currentStatusBar);
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

  // Set focus to mainwindow and then back to debug window when clicked on debugwindow
  connect(rt, &PdmRunTime::debugWindowFocused, [=]() {
    if(debugWindow){
//      this->show();
      this->raise();
//      this->activateWindow();
      debugWindow->raise();
    }
    emit rt->logc("Debug window focused.", "blue");
  });

  // Set focus to debug window when clicked on mainwindow
  connect(rt, &PdmRunTime::mainWindowFocused, [=]() {
    if(debugWindow){
      debugWindow->raise();
      this->raise();
    }
    emit rt->logc("Main window focused.", "blue");
  });


  // Setup framelesshelper menubar.
  QTimer::singleShot(0, this, &MainWindow::setupFramelesshelperWindow);

  connect(FramelessWidgetsHelper::get(this), &wangwenx190::FramelessHelper::FramelessWidgetsHelper::ready, [=]() {
    connect(moveTimer, &PdmUpdateTimer::timeout, this, &MainWindow::onMoveTimerTimeout);
    connect(resizeTimer, &PdmUpdateTimer::timeout, this, &MainWindow::onResizeTimerTimeout);

    //Default geometry for the main window
    QWidget tempWidget;
    tempWidget.setGeometry(847, 236, defaultWidth, 905);
    QSettings settings;
    // Restore the previous window geometry
    restoreGeometry(settings.value("mainwindow/geometry",tempWidget.saveGeometry()).toByteArray());

    // Set the initial position of the splitter's handle
    QList<int> initialSizes;
    initialSizes << defaultWidth/5*2 << defaultWidth-defaultWidth/5*2;
    ui->splitter->setSizes(initialSizes);

    // Restore previous sessions' windows opened and their geometry
    QTimer::singleShot(0, [this]() { debugWindow->checkAndShow(); });
    // Check existing user, if exist ask for decryption password
    QTimer::singleShot(0, rt, &PdmRunTime::checkExistingUser);


  });

  // Remove the default tab .
  mainwindowTabCloseRequested(0);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete debugWindow;
  delete rt;
  delete moveTimer;
  delete resizeTimer;
  delete static_cast<QPropertyAnimation*>( animation);
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
  }

  debugWindow->show();
}

void MainWindow::mainwindowNoteCreateSuccess() {
  rt->runCmd("note_refresh_list");
}

// Helpers

void MainWindow::newSettingsWindow() {
  if (!settingsWindow){
    settingsWindow = new SettingsMainWindow(ui->centralwidget, rt);
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
  if (rt->getCmd("showUsernameInStatusBar")) {
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

void MainWindow::setupFramelesshelperWindow(){
#ifdef PDM_USE_FRAMELESSHELPER
  m_titleBar = new StandardTitleBar(this);
  m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);
  setContentsMargins(0,0,0,0); // set the margin of the window that contains the shadow
  FramelessWidgetsHelper::get(this)->extendsContentIntoTitleBar();

  auto * titleBar = new QWidget(this);
  auto * layout = new QHBoxLayout(this);
  layout->setContentsMargins(5, 0, 5, 0);
  layout->setSpacing(5);
  titleBar->setLayout(layout);

  statusCircle = new FlashingCircle(this);
  animation = Animated::makeAnimateAlpha(static_cast<FlashingCircle *>(statusCircle), this);
  static_cast<QPropertyAnimation*>(animation)->start();
  layout->addWidget(static_cast<FlashingCircle *>(statusCircle));
#ifndef Q_OS_MACOS
  auto *pdmIcon = new QPushButton(this);
  pdmIcon->setText("");
  pdmIcon->setIcon(QIcon(":/images/icon/icon_small"));
  pdmIcon->setIconSize(QSize(20, 20));
  pdmIcon->setMinimumHeight(20);
  pdmIcon->setMaximumHeight(20);
  pdmIcon->setStyleSheet(
      "QPushButton { background-color: none; border: none; } QPushButton:hover { background-color: none; border: none; }");
#endif // Q_OS_MACOS

  QMenuBar *const mb = menuBar();
//  mb->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
  mb->setStyleSheet(FRAMELESSHELPER_STRING_LITERAL(R"(
QMenuBar {
  background-color: transparent;
}

QMenuBar::item {
  background: transparent;
}

QMenuBar::item:selected {
  background: #a8a8a8;
}

QMenuBar::item:pressed {
  background: #888888;
}
  )"));
  const auto titleBarLayout = static_cast<QHBoxLayout *>(m_titleBar->layout());
#ifndef Q_OS_MACOS
  titleBarLayout->insertWidget(0, pdmIcon);
  titleBarLayout->insertWidget(1, mb);
  titleBarLayout->insertWidget(2, titleBar);
#else
  titleBarLayout->insertWidget(0, mb);
  titleBarLayout->insertWidget(1, titleBar);
#endif //Q_OS_MACOS

  // If windows or linux insert stretch at 2, macos insert stretch at 0.
  if (QSysInfo::productType() == "windows" || QSysInfo::productType() == "linux") {
    titleBarLayout->insertStretch(2, 1);
  } else {
    titleBarLayout->insertStretch(1, 1);
  }

  // setMenuWidget(): make the menu widget become the first row of the window.
  setMenuWidget(m_titleBar);

  FramelessWidgetsHelper::get(this)->setTitleBarWidget(m_titleBar);
#ifndef Q_OS_MACOS
  FramelessWidgetsHelper::get(this)->setSystemButton(m_titleBar->minimizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Minimize);
  FramelessWidgetsHelper::get(this)->setSystemButton(m_titleBar->maximizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Maximize);
  FramelessWidgetsHelper::get(this)->setSystemButton(m_titleBar->closeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Close);
#endif // Q_OS_MACOS
  FramelessWidgetsHelper::get(this)->setHitTestVisible(mb); // IMPORTANT!
  FramelessWidgetsHelper::get(this)->setHitTestVisible(titleBar); // IMPORTANT!
#ifndef Q_OS_MACOS
  FramelessWidgetsHelper::get(this)->setHitTestVisible(pdmIcon); // IMPORTANT!
#endif // Q_OS_MACOS

  setWindowTitle("PDM Notes");

  // Unset the frameless flag
  setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
  show();


#else
//
//// Create the custom status circle and animation
//  statusCircle = new FlashingCircle(this);
//  animation = Animated::makeAnimateAlpha(static_cast<FlashingCircle *>(statusCircle), this);
//  static_cast<QPropertyAnimation*>(animation)->start();
//
//// Layout for the custom status circle
////  QHBoxLayout *statusLayout = new QHBoxLayout;
////  statusLayout->setContentsMargins(5, 0, 5, 0); // Set the margins of the status circle
////  statusLayout->setContentsMargins(0, 0, 0, 0); // Set the margins of the status circle
////  statusLayout->addWidget(static_cast<FlashingCircle *>(statusCircle));
////
////  QWidget *statusContainerWidget = new QWidget(this);
////  statusContainerWidget->setStyleSheet("background-color: transparent;"); // Set the background color of the status circle
////  statusContainerWidget->setLayout(statusLayout);
//
//// New central layout which will hold everything
//  QVBoxLayout *centralLayout = new QVBoxLayout;
//  centralLayout->setContentsMargins(0, 0, 0, 0);
//  centralLayout->setSpacing(0);
//
//// Layout for the menubar and custom status circle
//  QHBoxLayout *menuLayout = new QHBoxLayout;
//  menuLayout->addWidget(ui->menubar);  // Your original menu bar
//  menuLayout->setContentsMargins(4, 0, 4, 0);
//  menuLayout->addWidget(static_cast<FlashingCircle *>(statusCircle));
//
//  centralLayout->addLayout(menuLayout);
//  centralLayout->addWidget(ui->centralwidget);  // Your original central widget
//
//// Create a new central widget and set the layout to it
//  QWidget *newCentralWidget = new QWidget(this);
//  newCentralWidget->setLayout(centralLayout);
//  setCentralWidget(newCentralWidget);

#endif // PDM_USE_FRAMELESSHELPER
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

/**
 * Note is received in the local data store.
 *
 * Get the note from the local data store.
 * This function creates a new NoteEdit widget and adds it to the tab widget.
 * If the note already exists in the tab widget, it will switch to that tab.
 * Put the note contents in the tab widget.
 *
 * @brief MainWindow::mainwindowNoteRetrieveSuccess
 * @param noteId The note id of the note that was retrieved.
 * */
void MainWindow::mainwindowNoteRetrieveSuccess(int noteId) {
  emit rt->log("Note open/retrieve received.", "#C22A1C");
  PDM::NoteMsg note ;
  rt->user_data->getNote(noteId,&note);
  if(noteEditMap.contains(note.note_id)) { // Check if this already exists in the tab widget.
    ui->tabWidget->setCurrentIndex(noteEditMap[note.note_id]->idx);
    // If the note has a title, use that. Otherwise, use the note id.
    std::string tmpTitle =  !note.head.empty()? note.head: "Unnamed Note "+std::to_string(noteId);
    ui->tabWidget->setTabText(noteEditMap[note.note_id]->idx, tmpTitle.c_str());
    noteEditMap[note.note_id]->setFocus();
    return;
  }
  auto * noteEdit= new NoteEdit(note, this, rt);
  noteEditMap.insert(note.note_id, noteEdit); // Add to the map
  noteEdit->setNote();
  noteEdit->setProperty("dataKey", note.note_id.c_str());
  // If the note has a title, use that. Otherwise, use the note id.
  std::string tmpTitle =  !note.head.empty()? note.head: "Unnamed Note "+std::to_string(noteId);

  int tabIndex = ui->tabWidget->addTab(noteEdit, tmpTitle.c_str());
  ui->tabWidget->setCurrentIndex(tabIndex);
  noteEdit->idx=tabIndex;
  noteEdit->openedNoteId = noteId;
  noteEdit->setFocus();

}


void MainWindow::mainwindowNoteUpdateSuccess(int noteId) {
  emit rt->log("Note update received in mainwindow.", "#C22A1C");
  PDM::NoteMsg note ;
  rt->user_data->getNote(noteId, &note);
  if(noteEditMap.contains(note.note_id)) { // Check if this already exists in the tab widget.
    noteEditMap[note.note_id]->setNote();
    return;
  }
}

void MainWindow::mainwindowTabCloseRequested(int index){
  emit rt->log("Tab close requested: " + QString::number(index), "#C22A1C");
  QWidget *widget = ui->tabWidget->widget(index);
  auto dataKey = widget->property("dataKey").toString();
  ui->tabWidget->removeTab(index);
  noteEditMap.remove(dataKey.toStdString().c_str());
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

void MainWindow::mainwindowNoteListRightClicked(const QModelIndex &index) {

}

void MainWindow::closeEvent(QCloseEvent *event)
{
  if(debugWindow->isVisible()) debugWindow->close();

  // If you want to proceed with the close action:
  event->accept();
  rt->isClosing = 1;
  // If you want to prevent the window from closing:
  // event->ignore();
}

void MainWindow::mainwindowRuntimeStatusChanged(const QString &status) {

}

void MainWindow::showUsernameInStatusBar(int i) {
  if (rt->wt.userinfo.username.empty()) return;
  if (i==1) {
    statusBar()->showMessage(rt->wt.userinfo.username.c_str()); // Show username in status bar.
    rt->currentStatusBar = rt->wt.userinfo.username.c_str();
  }
  else {
    statusBar()->showMessage(""); // Hide warning message.
    rt->currentStatusBar = "";
  }
  statusBar()->setToolTip("");
}

void MainWindow::onNoteAdded(int index) {
  rt->logc_std("[MainWindow::onNoteAdded] notesListView->model()->rowCount()="+
    std::to_string(notesListView->model()->rowCount())+
    ", index="+std::to_string(index), "orange");
  if (index >= 0 && index < notesListView->model()->rowCount()) {
    QModelIndex modelIndex = notesListView->model()->index(index, 0);
    notesListView->scrollTo(modelIndex);
  }
}

bool MainWindow::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::WindowActivate:
      if (!rt->mainWindowFocusedState) {
        rt->mainWindowFocusedState = true;
        emit rt->mainWindowFocused();
      }
      else {
        rt->mainWindowFocusedState = false;
      }
      break;
    case QEvent::WindowDeactivate:
      emit rt->mainWindowBlured();
      break;
    default:
      break;
  }
  return QMainWindow::event(event);
}

void MainWindow::mainwindowNoteRename(int noteId) {
  emit rt->logc_std("[MainWindow::mainwindowNoteRename] noteId="+std::to_string(noteId), "orange");
  PDM::NoteMsg note ;
  rt->user_data->getNote(noteId, &note);
  if(noteEditMap.contains(note.note_id)) { // Check if this already exists in the tab widget.
    // If the note has a title, use that. Otherwise, use the note id.
    std::string tmpTitle =  !note.head.empty()? note.head: "Unnamed Note "+std::to_string(noteId);
    ui->tabWidget->setTabText(noteEditMap[note.note_id]->idx, tmpTitle.c_str());
    return;
  }
}
