#ifndef SETTINGSMAINWINDOW_H
#define SETTINGSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SettingsMainWindow;
}

class SettingsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsMainWindow(QWidget *parent = nullptr);
    ~SettingsMainWindow();

private:
    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
