#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Global>

#include "src/settings/settingsmainwindow.h"
#include "src/settings/accountwidget.h"
#include "src/others/debugwindow.h"
#include "PdmRunTime.h"
#include "notesView/NotesScroll.h"
#include "notesView/NoteEdit.h"
#include <FramelessHelper/Widgets/framelessmainwindow.h>

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
  void*statusCircle=nullptr; // FlashingCircle
  void * animation=nullptr;
private slots:
  void on_actionSettings_triggered();
  void on_actionAccount_triggered();
  void on_actionDebug_Messages_triggered();
  void on_actionOpen_triggered();
  void mainwindowLoginSuccess();
  void mainwindowNoteHeadsSuccess();
  void mainwindowNoteRetrieveSuccess(int noteId);
  void open_user_database_location();
  void onMoveTimerTimeout();
  void onResizeTimerTimeout();
  void mainwindowNoteListLeftClicked(const QModelIndex &index);
  void mainwindowNoteListRightClicked(const QModelIndex &index);
  void mainwindowTabCloseRequested(int index);

  void on_actionZoom_In_triggered();

  void on_actionZoom_Out_triggered();

  protected:
  void moveEvent(QMoveEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

private:
  PdmUpdateTimer * moveTimer;
  PdmUpdateTimer * resizeTimer;
  Ui::MainWindow * ui;
  QMap<std::string, NoteEdit*> noteEditMap;
  StandardTitleBar * m_titleBar = nullptr;


  void newSettingsWindow();
  int defaultWidth = 866;
  void makeCustomTitleBar();

};
#endif // MAINWINDOW_H
