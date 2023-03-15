#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include "CustomWindow.h"
#include "shadowFrameWidget.h"


class DebugWindow :
        public QMainWindow
{
  Q_OBJECT

public:
  explicit DebugWindow(QWidget *parent = nullptr);
  ~DebugWindow();

  void toggleMaximize();

public slots:
  void appendMessage(const QString &message, const  QString &color = "#000000");
  void setWindowPosition(QPoint &a);
  void onKeepOnTopButtonClicked();
private slots:
  void on_actionOpen_One_Note_Page_triggered();
public:
  QTextEdit* texts;
  CustomTitleBar *titleBar;
  ShadowFrameWidget* shadowFrameWidget;
  QVBoxLayout *shadowWidgetLayout;

  QVBoxLayout *verticalLayout;
  QWidget *mainContent ; // Create the main content for your window
};

#endif // DEBUGWINDOW_H
