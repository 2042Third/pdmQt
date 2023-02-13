#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>

namespace Ui {
class DebugWindow;
}

class DebugWindow :
        public QMainWindow
{
    Q_OBJECT

public:
    explicit DebugWindow(QWidget *parent = nullptr);
    ~DebugWindow();
public slots:
    void appendMessage(const QString &message, const  QString &color = "#000000");

private:
    Ui::DebugWindow *ui;
    QTextEdit* texts;
};

#endif // DEBUGWINDOW_H
