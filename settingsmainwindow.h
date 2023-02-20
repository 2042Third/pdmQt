#ifndef SETTINGSMAINWINDOW_H
#define SETTINGSMAINWINDOW_H

#include <QMainWindow>
#include "accountwidget.h"
#include "informationwidget.h"
#include "PdmRunTime.h"
#include "PdmRuntimeRef.h"

namespace Ui {
class SettingsMainWindow;
}

class SettingsMainWindow : public QMainWindow, public PdmRuntimeRef
{
    Q_OBJECT

public:
    explicit SettingsMainWindow(QWidget *parent = nullptr);
    ~SettingsMainWindow();

    void navToAccount() {on_settingAccountButton_released();}

  AccountWidget * acc_ui;
  InformationWidget * info_ui;

private slots:
    void on_settingAccountButton_released();

    void on_settingInfoButton_released();

private:

    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
