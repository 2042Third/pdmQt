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

    void navToAccount() {on_settingAccountButton_released();}

    QWidget * acc_ui;
    QWidget * info_ui;

signals:
    void log(const QString &message, const  QString &color );

private slots:
    void on_settingAccountButton_released();

    void on_settingInfoButton_released();

private:
    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
