#include <QPushButton>
#include <QSettings>
#include "debugwindow.h"
#include <QToolBar>
#include <QWindow>
#include <QMenuBar>

#include <QCheckBox>
#include "helpers/Animated.h"
#include <QtWidgets/qfileiconprovider.h>
#include <QSplitter>
#include <QListWidget>
#include <QStackedWidget>
#include <QAbstractButton>
#include <QToolButton>
#ifdef PDM_USE_FRAMELESSHELPER
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#endif // PDM_USE_FRAMELESSHELPER
#include "macOSWindowBridge.h"
#include "src/others/tools/pdmQtWidgets.h"
#include "PdmRunTime.h"
#include "mainwindow.h"
#include "helpers/FlashingCircle.h"
#include "debugwindowCommandWidget.h"
#include <QSpinBox>
#include <QComboBox>
#include <QFormLayout>
//WId winId = reinterpret_cast<WId>(createNativeMacOSWindow());
//  extern "C" WId createNativeMacOSWindow();
DebugWindow::DebugWindow(QWidget *parent,PdmRunTime*r) :
  QMainWindow(parent, Qt::FramelessWindowHint),
  PdmRuntimeRef(r)
{

  setAttribute(Qt::WA_TranslucentBackground);
  mainContent = new QWidget(); // Basically central widget
  shadowFrameWidget = new QWidget(this); // init the shadow drop
//  shadowFrameWidget = new ShadowFrameWidget(this); // init the shadow drop

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

  moveTimer = new PdmUpdateTimer(3000,this);
  resizeTimer = new PdmUpdateTimer(3000,this);
  connect(moveTimer, &PdmUpdateTimer::timeout, this, &DebugWindow::onMoveTimerTimeout);
  connect(resizeTimer, &PdmUpdateTimer::timeout, this, &DebugWindow::onResizeTimerTimeout);


  // Connect the custom button to staying this debug window on top.
  titleBar->customButton->setIcon(QIcon(":/images/icon/pin"));
  titleBar->customButton->setToolTip("Toggle pin on top (currently not pinned)" );
  connect(titleBar->customButton, &QPushButton::clicked, this, &DebugWindow::onKeepOnTopButtonClicked);

  // Set the layout for the custom title bar window
  setCentralWidget(shadowFrameWidget);

#ifndef PDM_USE_FRAMELESSHELPER
  shadowWidgetLayout->addWidget(titleBar); // custom titlebar
#endif
  shadowWidgetLayout->addWidget(texts); // main content, the console

  // pdm_command line widget
  auto *commandWidget = new CommandWidget(this, rt);
  shadowWidgetLayout->addWidget(commandWidget);

  // add the splitter settings
  auto splitterSettings= makeDebugSettings(shadowFrameWidget,shadowWidgetLayout);

  shadowFrameWidget->setLayout(shadowWidgetLayout);

  // Set the textEdit background as gray
  texts->setStyleSheet("background-color: #FFFFFF;");


  // Setup frameless window if on using frameless helper
#ifdef PDM_USE_FRAMELESSHELPER
  QTimer::singleShot(0, this, &DebugWindow::makeCustomWindow);
#endif
}

void DebugWindow::appendMessage(const QString &message, const QString &color)
{
  QString html = QString("<font color=%1>%2</font>").arg(color, message);
  texts->append(html);
}

DebugWindow::~DebugWindow()
{
//  delete m_mainWindow;
#ifdef Q_OS_MACOS

#endif // Q_OS_MACOS
}

QWidget* DebugWindow::makeDebugSettings(QWidget* widget, QLayout* layout){

  auto *collapsibleFrame= PDM::addCollapsibleFrame("More Debug Settings", layout,widget);

  // Create a vertical splitter
  auto *splitter = new QSplitter(Qt::Horizontal, widget);
  QVBoxLayout *frameLayout = new QVBoxLayout(collapsibleFrame);
  frameLayout->addWidget(splitter);

  // Create the left widget for settings types
  auto *listWidget = new QListWidget(splitter);
  listWidget->addItem("General");
  listWidget->addItem("Status");
  listWidget->addItem("Window");

  // Create the right stacked widget for settings
  auto *stackedWidget = new QStackedWidget(splitter);
  stackedWidget->addWidget(new QLabel("General Settings"));
  stackedWidget->addWidget(getStatusWidget(widget));
  stackedWidget->addWidget(getMoreSettingsWidget(widget));

  splitter->addWidget(listWidget);
  splitter->addWidget(stackedWidget);

  // Link the left and right side so the right shows the correct page
  connect(listWidget, &QListWidget::currentRowChanged,
          stackedWidget, &QStackedWidget::setCurrentIndex);

  return splitter;
}

void DebugWindow::openCustomWindow() {
#ifdef PDM_USE_FRAMELESSHELPER
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
  helper->setSystemButton(m_titleBar->minimizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Minimize);
  helper->setSystemButton(m_titleBar->maximizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Maximize);
  helper->setSystemButton(m_titleBar->closeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Close);
#endif // Q_OS_MACOS
  helper->setHitTestVisible(mb); // IMPORTANT!
  helper->setHitTestVisible(titlebarButton); // IMPORTANT!
  m_mainWindow->setWindowTitle("FramelessHelper demo application - QMainWindow");
  mb->setWindowTitle("FramelessHelper demo application - QMenuBar");
  m_mainWindow->setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
  m_mainWindow->show();
#endif // PDM_USE_FRAMELESSHELPER
}

void DebugWindow::makeCustomWindow() {
#ifdef PDM_USE_FRAMELESSHELPER
  if (m_titleBar == nullptr) {
    m_titleBar = new StandardTitleBar(this);
  }
  m_titleBar->setTitleLabelAlignment(Qt::AlignCenter);
  setContentsMargins(0,0,0,0); // set the margin of the window that contains the shadow
//  m_mainWindow = new QMainWindow();
  resize(500, 500);

  QMenuBar * const mb = menuBar();
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
  titleBarLayout->insertWidget(0, mb);
  titleBarLayout->insertWidget(1, titleBar);

  // If windows or linux insert stretch at 2, macos insert stretch at 0.
  if(QSysInfo::productType() == "windows" || QSysInfo::productType() == "linux"){
    titleBarLayout->insertStretch(1,1);
  }else{
    titleBarLayout->insertStretch(0,1);
  }

  // setMenuWidget(): make the menu widget become the first row of the window.
  setMenuWidget(m_titleBar);

  FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
  helper->setTitleBarWidget(m_titleBar);
#ifndef Q_OS_MACOS
  helper->setSystemButton(m_titleBar->minimizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Minimize);
  helper->setSystemButton(m_titleBar->maximizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Maximize);
  helper->setSystemButton(m_titleBar->closeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Close);
#endif // Q_OS_MACOS
  helper->setHitTestVisible(mb); // IMPORTANT!
  helper->setHitTestVisible(titleBar); // IMPORTANT!
  setWindowTitle("Debug Window");
//  setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
  // Unset the frameless flag
  setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
  show();
#endif
}

void DebugWindow::reopenFrameless()  {
  setContentsMargins(0,0,0,0); // set the margin of the window that contains the shadow
//  m_mainWindow = new QMainWindow();
  resize(500, 500);

  QMenuBar * const mb = menuBar();
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
  titleBarLayout->insertWidget(0, mb);
  titleBarLayout->insertWidget(1, titleBar);

  // If windows or linux insert stretch at 2, macos insert stretch at 0.
  if(QSysInfo::productType() == "windows" || QSysInfo::productType() == "linux"){
    titleBarLayout->insertStretch(1,1);
  }else{
    titleBarLayout->insertStretch(0,1);
  }

  // setMenuWidget(): make the menu widget become the first row of the window.
  setMenuWidget(m_titleBar);

  FramelessWidgetsHelper *helper = FramelessWidgetsHelper::get(this);
  helper->setTitleBarWidget(m_titleBar);
#ifndef Q_OS_MACOS
  helper->setSystemButton(m_titleBar->minimizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Minimize);
  helper->setSystemButton(m_titleBar->maximizeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Maximize);
  helper->setSystemButton(m_titleBar->closeButton(), wangwenx190::FramelessHelper::Global::SystemButtonType::Close);
#endif // Q_OS_MACOS
  helper->setHitTestVisible(mb); // IMPORTANT!
  helper->setHitTestVisible(titleBar); // IMPORTANT!
  setWindowTitle("Debug Window");
//  setWindowIcon(QFileIconProvider().icon(QFileIconProvider::Computer));
  // Unset the frameless flag
  setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
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
    //Default geometry for the main window
    QWidget tempWidget;
    tempWidget.setGeometry(500, 500, 600, 500);

    QSettings settings;
    // Restore the previous window geometry
    restoreGeometry(settings.value("debugwindow/geometry",tempWidget.saveGeometry()).toByteArray());


//    move(QPoint(settings.value("debugwindow/positionX",500).toInt()
//                , settings.value("debugwindow/positionY",500).toInt()));
    raise(); // Bring the window to the front
  }
}

QWidget *DebugWindow::getMoreSettingsWidget(QWidget *pWidget) {
  auto *widget = new QWidget(pWidget);
  auto* layout = new QVBoxLayout(widget);

  // Action buttons
  button1 = new QPushButton();
  button2 = new QPushButton();
  button3 = new QPushButton();

  layout->addWidget(button1);
  layout->addWidget(button2);
#ifdef PDM_USE_FRAMELESSHELPER
  layout->addWidget(button3);
#endif
  // qt implementation custom window
  button1->setText("Open Custom Window (native with custom titlebar)");
  connect(button1, &QPushButton::clicked, this, &DebugWindow::openCustomWindow);

  // MacOS AppKit implementation of custom window
  button2->setText("Open MacOS Window (native with custom titlebar) (MacOS)");
  connect(button2, &QPushButton::clicked, this, &DebugWindow::openMacOSCustomWindow);

#ifdef PDM_USE_FRAMELESSHELPER
  // Convert current window to frameless helper
  button3->setText("Convert current window to frameless helper");
  connect(button3, &QPushButton::clicked, this, &DebugWindow::makeCustomWindow);
#endif
  return widget;
}

QWidget *DebugWindow::getStatusWidget(QWidget *pWidget) {
  auto *widget = new QWidget(pWidget);
  auto* layout = new QVBoxLayout(widget);
  QWidget *colorSelectWidget = getStatusColorWidget(pWidget);
  layout->addWidget(colorSelectWidget);
  return widget;
}

QWidget *DebugWindow::getStatusColorWidget( QWidget *pWidget) const {
  auto *colorSelectWidget = new PDM::ExtraQt::UpdatingWidget(pWidget);
  auto *colorSelectLayout = new QFormLayout(colorSelectWidget);       // Use QVBoxLayout to place widgets vertically



  auto *nameSelect = new QComboBox();
  nameSelect->addItems(QColor::colorNames());
  colorSelectLayout->addRow("Change Status Color", nameSelect);
  connect(nameSelect, &QComboBox::currentTextChanged,
          [ this](const QString &text){
              rt->changeMainwindowStatusColor(text);
          });

  auto *checkBox = new QCheckBox("Status Flashing Animation");
  colorSelectLayout->addRow("Show Status Circle", checkBox);
  checkBox->setCheckState(Qt::CheckState::Checked);
  connect(checkBox, &QCheckBox::stateChanged, [this](int state){
      PdmRunTime::toggleAnimation(rt, state);
  });

  auto *animationSpeedSpinBox = new QSpinBox();
  animationSpeedSpinBox->setRange(0, 5000);
  colorSelectLayout->addRow("Animation Speed", animationSpeedSpinBox);
  QObject::connect(animationSpeedSpinBox, &QSpinBox::valueChanged, [this](int value) {
      PdmRunTime::changeAnimationSpeed(rt, value);
  });

  connect(colorSelectWidget,&PDM::ExtraQt::UpdatingWidget::widgetShown
          , [this,nameSelect, checkBox, animationSpeedSpinBox](){
            if (static_cast<MainWindow *>(rt->main_window) && static_cast<MainWindow *>(rt->main_window)->animation) {
              nameSelect->setCurrentText(
                  static_cast<FlashingCircle*>(static_cast<MainWindow *>(rt->main_window)->statusCircle)
                  ->getColorName());
              auto* ani = static_cast<QPropertyAnimation*>(static_cast<MainWindow *>(rt->main_window)->animation);
              if(ani->state() == QAbstractAnimation::Running) {
                checkBox->setCheckState(Qt::CheckState::Checked);
              } else {
                checkBox->setCheckState(Qt::CheckState::Unchecked);
              }
              animationSpeedSpinBox->setValue(ani->duration());
            }
          });

  return colorSelectWidget;
}

void DebugWindow::appendMessageC(const QString &message, const QString &color) {
  QString html = QString("<font color=%1>%2</font>").arg(PDM::Helpers::QtColor::get_color_rgb(color), message);
  texts->append(html);
}
void DebugWindow::appendMessage_std(const std::string &message, const std::string &color) {
  QString html = QString("<font color=%1>%2</font>")
      .arg(PDM::Helpers::QtColor::get_color_rgb(QString::fromStdString(color))
           , QString::fromStdString(message)
          );
  texts->append(message.c_str());
}
void DebugWindow::appendMessageC_std(const std::string &message, const std::string &color) {
  QString html = QString("<font color=%1>%2</font>")
      .arg(PDM::Helpers::QtColor::get_color_rgb(QString::fromStdString(color))
          , QString::fromStdString(message)
      );
  texts->append(html);
}

bool DebugWindow::event(QEvent *event) {
//  qDebug() << "Event type:" << event->type();
  switch (event->type()) {
    case QEvent::WindowActivate:
      if (!rt->debugWindowFocusedState) {
        rt->debugWindowFocusedState = true;
        emit rt->debugWindowFocused();
      }
      else {
        rt->debugWindowFocusedState = false;
      }
      break;
    case QEvent::WindowDeactivate:
      emit rt->debugWindowBlurred();
      break;
    default:
      break;
  }
  return QMainWindow::event(event);
}

void DebugWindow::closeEvent(QCloseEvent *event) {
//  QWidget::closeEvent(event);
  debugWindowCloseButton();
  event->ignore();
  hide();
}

void DebugWindow::moveEvent(QMoveEvent *event) {
  QMainWindow::moveEvent(event);
  // Start the timer when the window is moved
  moveTimer->start();
}
void DebugWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  // Start the timer when the window is resized
  resizeTimer->start();
}

void DebugWindow::onMoveTimerTimeout() {
  emit rt->logc("Debug window stopped moving: ", "red");
  emit rt->log("  Final position: " + QString::number(this->x()) + ", " + QString::number(this->y())
               , "red");
  QSettings settings;
  settings.setValue("debugwindow/geometry", saveGeometry());
}

void DebugWindow::onResizeTimerTimeout() {
  emit rt->log("Debug window stopped resizing: ", "#C22A1C");
  emit rt->log("  Final size: " + QString::number(this->width()) + ", " + QString::number(this->height()), "#C22A1C");
  QSettings settings;
  settings.setValue("debugwindow/geometry", saveGeometry());
}


