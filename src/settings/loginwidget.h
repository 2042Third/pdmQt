#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "PdmRunTimeRef.h"

class LoginWidget: public QWidget, public PdmRunTimeRef
{
  Q_OBJECT
public:
  explicit LoginWidget(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~ LoginWidget();
private slots:
  void onLoginClicked();
  bool eventFilter(QObject *object, QEvent *event) override;

private:
  QLineEdit *m_emailEdit;
  QLineEdit *m_passwordEdit;
  QPushButton *m_loginButton;
};

#endif // LOGINWIDGET_H
