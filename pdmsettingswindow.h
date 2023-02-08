#ifndef PDMSETTINGSWINDOW_H
#define PDMSETTINGSWINDOW_H

#include <QWidget>

namespace Ui {
class PdmSettingsWindow;
}

class PdmSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PdmSettingsWindow(QWidget *parent = nullptr);
    ~PdmSettingsWindow();

private:
    Ui::PdmSettingsWindow *ui;
};

#endif // PDMSETTINGSWINDOW_H
