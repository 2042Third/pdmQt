#ifndef BUZYWIDGET_H
#define BUZYWIDGET_H

#include <QWidget>

namespace Ui {
class BuzyWidget;
}

class BuzyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BuzyWidget(QWidget *parent = nullptr);
    ~BuzyWidget();

private:
    Ui::BuzyWidget *ui;
};

#endif // BUZYWIDGET_H
