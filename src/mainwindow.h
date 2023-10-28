#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/settings/settingsmainwindow.h"
#include "src/settings/accountwidget.h"
#include "src/others/debugwindow.h"
#include "PdmRunTime.h"
#include "notesView/NotesScroll.h"
#include "notesView/NoteEdit.h"

#ifdef PDM_USE_FRAMELESSHELPER
#include <FramelessHelper/Widgets/framelessmainwindow.h>
#include <FramelessHelper/Core/framelesshelpercore_global.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#endif
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
  void * statusCircle=nullptr; // FlashingCircle
  void * animation=nullptr;
  void showUsernameInStatusBar(int i);
private slots:
  void on_actionSettings_triggered();
  void on_actionAccount_triggered();
  void on_actionDebug_Messages_triggered();
  void on_actionOpen_triggered();
  void mainwindowLoginSuccess();
  void mainwindowNoteHeadsSuccess();
  void mainwindowNoteRetrieveSuccess(int noteId);
  void mainwindowNoteUpdateSuccess(int noteId);
  void open_user_database_location();
  void onMoveTimerTimeout();
  void onResizeTimerTimeout();
  void mainwindowNoteListLeftClicked(const QModelIndex &index);
  void mainwindowNoteListRightClicked(const QModelIndex &index);
  void mainwindowTabCloseRequested(int index);
  void mainwindowRuntimeStatusChanged(const QString &status);
  void on_actionZoom_In_triggered(); // Defined in menu bar from QT creator
  void on_actionZoom_Out_triggered(); // Defined in menu bar from QT creator

  protected:
  void moveEvent(QMoveEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

private:
  PdmUpdateTimer * moveTimer;
  PdmUpdateTimer * resizeTimer;
  Ui::MainWindow * ui;
  QMap<std::string, NoteEdit*> noteEditMap;
#ifdef PDM_USE_FRAMELESSHELPER
  StandardTitleBar * m_titleBar = nullptr;
#endif // PDM_USE_FRAMELESSHELPER

  void newSettingsWindow();
  int defaultWidth = 866;
  void makeCustomTitleBar();

};
#endif // MAINWINDOW_H
