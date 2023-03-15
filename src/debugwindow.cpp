#include <QPushButton>
#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::DebugWindow)
{
  ui->setupUi(this);

  // After the setup of the designer;
  texts = new QTextEdit(ui->centralwidget);
  texts->setObjectName("textEdit");
  texts->setReadOnly(true);
  ui->verticalLayout->addWidget(texts);

  keepOnTopButton = new QPushButton("Toggle Stay On Top", this);
  connect(keepOnTopButton, &QPushButton::clicked, this, &DebugWindow::on_keepOnTopButton_clicked);

  // Custom windowing.
  // Set the custom title bar for the Debug window
  titleBar = new CustomTitleBar(this);
  setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
  setWindowTitle("Custom Title Bar Example");
  setCentralWidget(ui->centralwidget);
  setMenuWidget(titleBar);

  // Connect signals from the custom title bar to handle window actions
  connect(titleBar, &CustomTitleBar::minimizeWindow, this, &DebugWindow::showMinimized);
  connect(titleBar, &CustomTitleBar::maximizeWindow, this, &DebugWindow::toggleMaximize);
  connect(titleBar, &CustomTitleBar::closeWindow, this, &DebugWindow::close);

}
void DebugWindow::appendMessage(const QString &message, const QString &color)
{
    QString html = QString("<font color=%1>%2</font>").arg(color, message);
    texts->append(html);
}



DebugWindow::~DebugWindow()
{
    delete ui;
    delete texts;
    delete keepOnTopButton;
    delete titleBar;
}

void DebugWindow::on_actionOpen_One_Note_Page_triggered()
{

}

void DebugWindow::setWindowPosition(QPoint &a) {
  move(a);
}
void DebugWindow::on_keepOnTopButton_clicked()
{
  Qt::WindowFlags flags = windowFlags();
  // Toggle the Qt::WindowStaysOnTopHint flag using XOR
  setWindowFlags(flags ^ Qt::WindowStaysOnTopHint);
  show();
}


void DebugWindow::toggleMaximize() {
  if (isMaximized()) {
    showNormal();
  } else {
    showMaximized();
  }
}
