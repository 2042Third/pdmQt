#include <QPushButton>
#include <QSettings>
#include "debugwindow.h"
#include <QToolBar>
#include <QWindow>
#include <QMenuBar>
#include <FramelessWidgetsHelper>

#include <QtWidgets/qfileiconprovider.h>

#ifdef Q_OS_MAC
#include "macOSWindowBridge.h"
//WId winId = reinterpret_cast<WId>(createNativeMacOSWindow());
//  extern "C" WId createNativeMacOSWindow();
#endif
DebugWindow::DebugWindow(QWidget *parent) :
  QMainWindow(parent, Qt::FramelessWindowHint)
{

  setAttribute(Qt::WA_TranslucentBackground);
  mainContent = new QWidget(); // Basically central widget
  shadowFrameWidget = new ShadowFrameWidget(this); // init the shadow drop

  // After the setup of the designer;
  texts = new QTextEdit(mainContent);
  texts->setObjectName("textEdit");
  texts->setReadOnly(true);
  // Custom windowing.
  // Set the custom title bar for the Debug window
  titleBar = new CustomTitleBar(this);

  shadowWidgetLayout = new QVBoxLayout(shadowFrameWidget);
  setContentsMargins(5,5,5,5); // set the margin of the window that contains the shadow
  shadowWidgetLayout->setContentsMargins(5,5,5,5); // Adjust the margins to control the shadow size

  // Connect signals from the custom title bar to handle window actions
  connect(titleBar, &CustomTitleBar::minimizeWindow, this, &DebugWindow::showMinimized);
  connect(titleBar, &CustomTitleBar::maximizeWindow, this, &DebugWindow::toggleMaximize);
  connect(titleBar, &CustomTitleBar::closeWindow, this, &DebugWindow::close);
  connect(titleBar, &CustomTitleBar::closeWindow, this, &DebugWindow::debugWindowCloseButton);



  // Connect the custom button to staying this debug window on top.
  titleBar->customButton->setIcon(QIcon(":/images/icon/pin"));
  titleBar->customButton->setToolTip("Toggle pin on top (currently not pinned)" );
  connect(titleBar->customButton, &QPushButton::clicked, this, &DebugWindow::onKeepOnTopButtonClicked);

  // Set the layout for the custom title bar window
  setCentralWidget(shadowFrameWidget);

  // Action buttons

  button1 = new QPushButton();
  button1->setFixedSize(100, 50);  // Change these values to the size you want

  button2 = new QPushButton();
  button2->setFixedSize(100, 50);  // Change these values to the size you want

  button3 = new QPushButton();
  button3->setFixedSize(100, 50);  // Change these values to the size you want


  shadowWidgetLayout->addWidget(titleBar); // custom titlebar
  shadowWidgetLayout->addWidget(texts); // main content, the console
  shadowWidgetLayout->addWidget(button1);
  shadowWidgetLayout->addWidget(button2);
  shadowWidgetLayout->addWidget(button3);

  // qt implementation custom window
  button1->setText("Open Custom Window (native with custom titlebar)");
  connect(button1, &QPushButton::clicked, this, &DebugWindow::openCustomWindow);

  // MacOS AppKit implementation of custom window
  button2->setText("Open MacOS Window (native with custom titlebar) (MacOS)");
  connect(button2, &QPushButton::clicked, this, &DebugWindow::openMacOSCustomWindow);

  // Convert current window to frameless helper
  button3->setText("Convert current window to frameless helper");
  connect(button3, &QPushButton::clicked, this, &DebugWindow::makeCustomWindow);

  shadowFrameWidget->setLayout(shadowWidgetLayout);


  // Set the textEdit background as gray
  texts->setStyleSheet("background-color: #FFFFFF;");

  // Set the init size.
  resize(500, 500);
}

void DebugWindow::appendMessage(const QString &message, const QString &color)
{
  QString html = QString("<font color=%1>%2</font>").arg(color, message);
  texts->append(html);
}


DebugWindow::~DebugWindow()
{
  delete m_mainWindow;
#ifdef Q_OS_MACOS

#endif // Q_OS_MACOS
}

void DebugWindow::openCustomWindow() {
  m_titleBar = new StandardTitleBar(this);
  m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);
  m_mainWindow = new QMainWindow();
  m_mainWindow->resize(800, 600);
  m_mainWindow->setWindowTitle("FramelessHelper demo application - QMainWindow");

  QMenuBar * const mb = m_mainWindow->menuBar();
  mb->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
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
  titleBarLayout->insertWidget(0, mb);
  auto titlebarButton = new QPushButton(this);
  titlebarButton->setObjectName(QStringLiteral("action"));
  titlebarButton->setText(tr("Action"));
  titleBarLayout->insertWidget(1, titlebarButton);
  // If windows or linux insert stretch at 2, macos insert stretch at 0.
  if(QSysInfo::productType() == "windows" || QSysInfo::productType() == "linux"){
    titleBarLayout->insertStretch(2,1);
  }else{
    titleBarLayout->insertStretch(0,1);
  }

  // setMenuWidget(): make the menu widget become the first row of the window.
  m_mainWindow->setMenuWidget(m_titleBar);

  FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(m_mainWindow);
  helper->setTitleBarWidget(m_titleBar);
#ifndef Q_OS_MACOS
  helper->setSystemButton(m_titleBar->minimizeButton(), SystemButtonType::Minimize);
    helper->setSystemButton(m_titleBar->maximizeButton(), SystemButtonType::Maximize);
    helper->setSystemButton(m_titleBar->closeButton(), SystemButtonType::Close);
#endif // Q_OS_MACOS
  helper->setHitTestVisible(mb); // IMPORTANT!
  helper->setHitTestVisible(titlebarButton); // IMPORTANT!
  m_mainWindow->setWindowTitle("FramelessHelper demo application - QMainWindow");
  mb->setWindowTitle("FramelessHelper demo application - QMenuBar");
  m_mainWindow->setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
  m_mainWindow->show();
}

void DebugWindow::makeCustomWindow() {
  m_titleBar = new StandardTitleBar(this);
  m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);
//  m_mainWindow = new QMainWindow();
  resize(800, 600);
  setWindowTitle("FramelessHelper demo application - QMainWindow");

  QMenuBar * const mb = menuBar();
  mb->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
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
  titleBarLayout->insertWidget(0, mb);
  auto titlebarButton = new QPushButton(this);
  titlebarButton->setObjectName(QStringLiteral("action"));
  titlebarButton->setText(tr("Action"));
  titleBarLayout->insertWidget(1, titlebarButton);
  // If windows or linux insert stretch at 2, macos insert stretch at 0.
  if(QSysInfo::productType() == "windows" || QSysInfo::productType() == "linux"){
    titleBarLayout->insertStretch(2,1);
  }else{
    titleBarLayout->insertStretch(0,1);
  }

  // setMenuWidget(): make the menu widget become the first row of the window.
 setMenuWidget(m_titleBar);

  FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
  helper->setTitleBarWidget(m_titleBar);
#ifndef Q_OS_MACOS
  helper->setSystemButton(m_titleBar->minimizeButton(), SystemButtonType::Minimize);
    helper->setSystemButton(m_titleBar->maximizeButton(), SystemButtonType::Maximize);
    helper->setSystemButton(m_titleBar->closeButton(), SystemButtonType::Close);
#endif // Q_OS_MACOS
  helper->setHitTestVisible(mb); // IMPORTANT!
  helper->setHitTestVisible(titlebarButton); // IMPORTANT!
  setWindowTitle("FramelessHelper demo application - QMainWindow");
  mb->setWindowTitle("FramelessHelper demo application - QMenuBar");
  setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
  // Unset the frameless flag
  setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
  show();

}

void DebugWindow::openMacOSCustomWindow() {
#ifdef Q_OS_MACOS
  void* view = (void*)createNativeMacOSWindow();

  QWidget* widget = QWidget::createWindowContainer(QWindow::fromWinId(WId(view)));
  widget->setMinimumSize(480, 300);

  // Add a QText with the word "Hello" to this native window
  QTextEdit *textEdit = new QTextEdit(widget);
  textEdit->setText("Hello");
  textEdit->setGeometry(10, 10, 100, 30);

  widget->show();
#else
  QMessageBox::information(this, "Not supported", "This feature is only supported on macOS");
#endif // Q_OS_MACOS
}

void DebugWindow::on_actionOpen_One_Note_Page_triggered()
{

}

void DebugWindow::setWindowPosition(QPoint &a) {
  move(a);
}

void DebugWindow::onKeepOnTopButtonClicked()
{
  Qt::WindowFlags flags = windowFlags();

  // Toggle the Qt::WindowStaysOnTopHint flag using XOR and update the icon
  setWindowFlags(flags ^ Qt::WindowStaysOnTopHint);

  titleBar->customButton->setIcon(flags & Qt::WindowStaysOnTopHint ? QIcon(":/images/icon/pin") : QIcon(":/images/icon/pin-off"));
  titleBar->customButton->setToolTip(flags & Qt::WindowStaysOnTopHint ? "Toggle pin on top (currently not pinned)": "Toggle pin on top (currently pinned)");

  show();
  raise(); // Bring the window to the front
}

void DebugWindow::toggleMaximize() {
  if (isMaximized()) {
    showNormal();
  } else {
    showMaximized();
  }
}

void DebugWindow::debugWindowCloseButton() {
  QSettings settings;
  settings.setValue("debugwindow/isopen", false);
}

void DebugWindow::show() {
  QWidget::show();

  // Set qsetting
  QSettings settings;
  settings.setValue("debugwindow/isopen", true);
}


void DebugWindow::checkAndShow() {
  QSettings settings;
  // After everything is settled, restore windows
  if (settings.value("debugwindow/isopen", false).toBool()){
    QWidget::show();
    move(QPoint(settings.value("debugwindow/positionX",500).toInt()
                , settings.value("debugwindow/positionY",500).toInt()));
    raise(); // Bring the window to the front
  }
}


