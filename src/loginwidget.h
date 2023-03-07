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
    void setRef(PdmRunTime*rtRef) override {
      PdmRuntimeRef::setRef(rtRef);
      emit rt->log("login widget Created","#00FF00");
    }
private slots:
    void onLoginClicked();
  bool eventFilter(QObject *object, QEvent *event) override;

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginButton;
};

#endif // LOGINWIDGET_H
