#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "PdmRuntimeRef.h"

class LoginWidget: public QWidget, public PdmRuntimeRef
{
  Q_OBJECT
public:
  explicit LoginWidget(QWidget *parent = nullptr);
  ~ LoginWidget();
  void setRef(PdmRunTime*rtRef) override ;
private slots:
  void onLoginClicked();
  bool eventFilter(QObject *object, QEvent *event) override;

private:
  QLineEdit *m_emailEdit;
  QLineEdit *m_passwordEdit;
  QPushButton *m_loginButton;
};

#endif // LOGINWIDGET_H
