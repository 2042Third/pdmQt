#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "settingsmainwindow.h"
#include "accountwidget.h"
#include "debugwindow.h"

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

private slots:
    void on_actionSettings_triggered();

    void on_actionAccount_triggered();

    void on_actionDebug_Messages_triggered();

private:
    Ui::MainWindow *ui;

  void newSettingsWindow();
};
#endif // MAINWINDOW_H
