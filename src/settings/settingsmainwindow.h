#ifndef SETTINGSMAINWINDOW_H
#define SETTINGSMAINWINDOW_H

#include <QMainWindow>
#include "accountwidget.h"
#include "informationwidget.h"
#include "PdmRunTime.h"
#include "PdmRuntimeRef.h"
#include "settingsmenuWidget.h"

namespace Ui {
class SettingsMainWindow;
}

class SettingsMainWindow : public QMainWindow, public PdmRuntimeRef
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
  void setRef(PdmRunTime* rtRef) override {
    PdmRuntimeRef::setRef(rtRef);
    acc_ui->setRef(rt);
    info_ui->setRef(rt);
    settings_ui->setRef(rt);
    emit rt->log("SettingsWidget widget Created","#00FF00");
  }

  QVector<QPushButton*> buttons;

private slots:
    void on_settingAccountButton_released();
    void on_settingInfoButton_released();
    void on_settingsSettingsButton_released();

private:

    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
