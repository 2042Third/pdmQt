#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>

#include "loginwidget.h"
namespace Ui {
class AccountWidget;
}

class AccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWidget(QWidget *parent = nullptr);
    ~AccountWidget();
    LoginWidget * loginWidget;

signals:
  void log(const QString &message, const QString &color);

private:
    Ui::AccountWidget *ui;
};

#endif // ACCOUNTWIDGET_H
