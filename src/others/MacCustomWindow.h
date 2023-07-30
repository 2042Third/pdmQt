//
// Created by Mike Yang on 2023/7/30.
//

#ifndef PDM_QT_MACCUSTOMWINDOW_H
#define PDM_QT_MACCUSTOMWINDOW_H
#include <QMainWindow>
#include <QGuiApplication>
#include <QWindow>

class MyMainWindow : public QMainWindow
{
public:
    MyMainWindow() : QMainWindow()
    {
      // Other setup code...

      setUnifiedTitleAndToolBarOnMac(true);  // This line is very important
    }

protected:
    void showEvent(QShowEvent *event) override
    {
      QMainWindow::showEvent(event);

//      // Get the NSWindow from the QWindow
//      NSWindow *nsWindow = qt_mac_window_for(this->windowHandle());
//
//      if (!nsWindow) return;
//
//      // Now you can do any NSWindow related thing
//      nsWindow.titleVisibility = NSWindowTitleHidden;
//      nsWindow.titlebarAppearsTransparent = YES;

      // More native code here...
    }
};
#endif //PDM_QT_MACCUSTOMWINDOW_H
