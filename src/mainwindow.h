#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/settings/settingsmainwindow.h"
#include "src/settings/accountwidget.h"
#include "src/others/debugwindow.h"
#include "PdmRunTime.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  DebugWindow * debugWindow;
  SettingsMainWindow * settingsWindow=nullptr;
  PdmRunTime* rt;

private slots:
  void on_actionSettings_triggered();
  void on_actionAccount_triggered();
  void on_actionDebug_Messages_triggered();
  void on_actionOpen_triggered();
  void mainwindowLoginSuccess();
  void open_user_database_location();
  void onWindowStateChanged(Qt::WindowState state);


private:
    Ui::MainWindow *ui;

  void newSettingsWindow();
};
#endif // MAINWINDOW_H
