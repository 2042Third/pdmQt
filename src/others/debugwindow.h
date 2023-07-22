#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include "CustomTitleBar.h"
#include "qgraphicseffect.h"
#include "shadowFrameWidget.h"
#include <QGraphicsDropShadowEffect>

class DebugWindow :
        public QMainWindow
{
  Q_OBJECT

public:
  explicit DebugWindow(QWidget *parent = nullptr);
  ~DebugWindow();

  void toggleMaximize();
  void show() ;

public slots:
  void appendMessage(const QString &message, const  QString &color = "#000000");
  void setWindowPosition(QPoint &a);
  void onKeepOnTopButtonClicked();
  void debugWindowCloseButton();

private slots:
  void on_actionOpen_One_Note_Page_triggered();
public:
  QTextEdit* texts;
  CustomTitleBar *titleBar;
  ShadowFrameWidget* shadowFrameWidget;
  QVBoxLayout *shadowWidgetLayout;
  QGraphicsDropShadowEffect *shadowEffect;

  QVBoxLayout *verticalLayout;
  QWidget *mainContent ; // Create the main content for your window
  void checkAndShow(); // MAYBE: move this to CustomWindow class
  QPushButton* button1;
  QPushButton* button2;
  QPushButton* button3;
};

#endif // DEBUGWINDOW_H
