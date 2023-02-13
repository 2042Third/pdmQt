#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class LoginWidget: public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~ LoginWidget();
private slots:
    void onLoginClicked();

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QPushButton *m_loginButton;
};

#endif // LOGINWIDGET_H
