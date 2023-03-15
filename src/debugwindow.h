#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include "CustomWindow.h"

namespace Ui {
class DebugWindow;
}

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
private:
  Ui::DebugWindow *ui;
  QTextEdit* texts;
  CustomTitleBar *titleBar;

};

#endif // DEBUGWINDOW_H
