#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include "CustomTitleBar.h"
#include "qgraphicseffect.h"
#include "shadowFrameWidget.h"
#include "PdmRuntimeRef.h"
#include "FramelessHelper/Widgets/framelesswidgetshelper.h"
#include <QGraphicsDropShadowEffect>
#ifdef PDM_USE_FRAMELESSHELPER
#include <FramelessHelper/Core/framelesshelpercore_global.h>

#include <FramelessHelper/Widgets/framelessmainwindow.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>

FRAMELESSHELPER_USE_NAMESPACE

FRAMELESSHELPER_BEGIN_NAMESPACE
    class StandardTitleBar;
FRAMELESSHELPER_END_NAMESPACE
#endif // PDM_USE_FRAMELESSHELPER

class DebugWindow :
        public QMainWindow,
        public PdmRuntimeRef
{
  Q_OBJECT


public:
  explicit DebugWindow(QWidget *parent = nullptr, PdmRunTime *r= nullptr);
  ~DebugWindow();

  void toggleMaximize();
  void show() ;

public slots:
  void appendMessage(const QString &message, const  QString &color = "#000000");
  void appendMessageC(const QString &message, const  QString &color = "black");
  void appendMessage_std(const std::string &message, const  std::string &color = "#000000");
  void appendMessageC_std(const std::string &message, const  std::string &color = "black");
  void setWindowPosition(QPoint &a);
  void onKeepOnTopButtonClicked();
  void debugWindowCloseButton();
protected:
  bool event(QEvent *event) override;
private slots:
  void on_actionOpen_One_Note_Page_triggered();
public:
  QTextEdit* texts;
  CustomTitleBar *titleBar;
  ShadowFrameWidget* shadowFrameWidget;
  QVBoxLayout *shadowWidgetLayout;

  QVBoxLayout *verticalLayout;
  QWidget *mainContent ; // Create the main content for your window
  void checkAndShow(); // MAYBE: move this to CustomWindow class
  QPushButton* button1;
  QPushButton* button2;
  QPushButton* button3;

  void openCustomWindow();
  void reopenFrameless() ;
  void openMacOSCustomWindow();
private:
#ifdef PDM_USE_FRAMELESSHELPER
    FRAMELESSHELPER_PREPEND_NAMESPACE(StandardTitleBar) *m_titleBar = nullptr;
#endif // PDM_USE_FRAMELESSHELPER
    QMainWindow *m_mainWindow = nullptr;

    void makeCustomWindow();


    QWidget *makeDebugSettings(QWidget *widget, QLayout *layout);

    QWidget *getMoreSettingsWidget(QWidget *pWidget);

    QWidget *getStatusWidget(QWidget *pWidget);

    QWidget *getStatusColorWidget( QWidget *pWidget) const;

};

#endif // DEBUGWINDOW_H
