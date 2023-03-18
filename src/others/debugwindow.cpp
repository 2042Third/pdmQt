#include <QPushButton>
#include "debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QMainWindow(parent, Qt::FramelessWindowHint)
{

  setAttribute(Qt::WA_TranslucentBackground);
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
  setContentsMargins(5,5,5,5); // set the margin of the window that contains the shadow
  shadowWidgetLayout->setContentsMargins(5,5,5,5); // Adjust the margins to control the shadow size
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

  shadowEffect = new QGraphicsDropShadowEffect(this);
  shadowEffect->setBlurRadius(10); // Adjust the blur radius for the desired shadow size
  shadowEffect->setOffset(0); // Set the offset to control the shadow position
  shadowEffect->setColor(QColor(0, 0, 0, 100)); // Adjust the color and opacity as needed

  // Apply the shadow effect to the main content widget
  shadowFrameWidget->setGraphicsEffect(shadowEffect);

  // Set the init size.
  resize(500, 400);
}

void DebugWindow::appendMessage(const QString &message, const QString &color)
{
    QString html = QString("<font color=%1>%2</font>").arg(color, message);
    texts->append(html);
}


DebugWindow::~DebugWindow()
{
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
  titleBar->customButton->setToolTip(flags & Qt::WindowStaysOnTopHint ? "Toggle pin on top (currently not pinned)"
                                                                      : "Toggle pin on top (currently pinned)");

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
