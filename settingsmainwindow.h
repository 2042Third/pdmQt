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
    bool destroyWidget();
    QWidget *lastWidget = nullptr;
    QWidget * acc_ui;
    QWidget * info_ui;

private slots:
    void on_settingAccountButton_released();

    void on_widget_customContextMenuRequested(const QPoint &pos);

    void on_settingInfoButton_released();

private:
    Ui::SettingsMainWindow *ui;
};

#endif // SETTINGSMAINWINDOW_H
