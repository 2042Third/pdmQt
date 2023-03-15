#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>

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
public slots:
  void appendMessage(const QString &message, const  QString &color = "#000000");
  void setWindowPosition(QPoint &a);
private slots:
  void on_actionOpen_One_Note_Page_triggered();
  void on_keepOnTopButton_clicked();
private:
  Ui::DebugWindow *ui;
  QTextEdit* texts;
};

#endif // DEBUGWINDOW_H
