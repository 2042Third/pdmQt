#ifndef SETTINGSMAINWINDOW_H
#define SETTINGSMAINWINDOW_H

#include <QMainWindow>
#include "accountwidget.h"
#include "informationwidget.h"
#include "PdmRunTimeRef.h"
#include "settingsmenuWidget.h"

namespace Ui {
class SettingsMainWindow;
}

class SettingsMainWindow : public QMainWindow, public PdmRunTimeRef
{
    Q_OBJECT

public:
  explicit SettingsMainWindow(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~SettingsMainWindow();

  void navToAccount() {on_settingAccountButton_released();}
  void setActiveButton(int idx);

  AccountWidget * acc_ui;
  InformationWidget * info_ui;
  settingsmenuWidget * settings_ui;

  QVector<QPushButton*> buttons;

private slots:
    void on_settingAccountButton_released();
    void on_settingInfoButton_released();
    void on_settingsSettingsButton_released();

private:

    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
