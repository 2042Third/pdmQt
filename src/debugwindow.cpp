#include <QPushButton>
#include "debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QMainWindow(parent, Qt::FramelessWindowHint)
{
  mainContent = new QWidget(); // Basically central widget
  verticalLayout = new QVBoxLayout(mainContent);
  shadowFrameWidget = new ShadowFrameWidget(this); // init the shadow drop

  // After the setup of the designer;
  texts = new QTextEdit(mainContent);
  texts->setObjectName("textEdit");
  texts->setReadOnly(true);
  verticalLayout->addWidget(texts);
  // Custom windowing.
  // Set the custom title bar for the Debug window
  titleBar = new CustomTitleBar(this);

  shadowWidgetLayout = new QVBoxLayout(shadowFrameWidget);
  shadowWidgetLayout->setContentsMargins(10, 10, 10, 10); // Adjust the margins to control the shadow size
  shadowWidgetLayout->addWidget(titleBar); // custom titlebar
  shadowWidgetLayout->addWidget(texts); // main content, the console
  shadowFrameWidget->setLayout(shadowWidgetLayout);

  // Connect signals from the custom title bar to handle window actions
  connect(titleBar, &CustomTitleBar::minimizeWindow, this, &DebugWindow::showMinimized);
  connect(titleBar, &CustomTitleBar::maximizeWindow, this, &DebugWindow::toggleMaximize);
  connect(titleBar, &CustomTitleBar::closeWindow, this, &DebugWindow::close);

  // Connect the custom button to staying this debug window on top.
  titleBar->customButton->setIcon(QIcon(":/images/icon/pin"));
  titleBar->customButton->setToolTip("Toggle pin on top (currently not pinned)" );
  connect(titleBar->customButton, &QPushButton::clicked, this, &DebugWindow::onKeepOnTopButtonClicked);

  // Set the layout for the custom title bar window
  setCentralWidget(shadowFrameWidget);
}

void DebugWindow::appendMessage(const QString &message, const QString &color)
{
    QString html = QString("<font color=%1>%2</font>").arg(color, message);
    texts->append(html);
}


DebugWindow::~DebugWindow()
{
  delete texts;
  delete titleBar;
  delete shadowFrameWidget;
  delete shadowWidgetLayout;
  delete mainContent;
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
  titleBar->customButton->setIcon(flags & Qt::WindowStaysOnTopHint ? QIcon(":/images/icon/pin") : QIcon (":/images/icon/pin-off"));
  titleBar->customButton->setToolTip(flags & Qt::WindowStaysOnTopHint ? "Toggle pin on top (currently not pinned)"
  : "Toggle pin on top (currently pinned)");
  show();
}

void DebugWindow::toggleMaximize() {
  if (isMaximized()) {
    showNormal();
  } else {
    showMaximized();
  }
}
