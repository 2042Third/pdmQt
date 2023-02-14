#include "loginwidget.h"
#include <QFormLayout>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    m_usernameEdit = new QLineEdit(this);
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    m_loginButton = new QPushButton("Login", this);
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow("Username:", m_usernameEdit);
    formLayout->addRow("Password:", m_passwordEdit);
    formLayout->addRow(m_loginButton);

    setLayout(formLayout);
}
void LoginWidget::onLoginClicked()
{

  QString username = m_usernameEdit->text();
  QString password = m_passwordEdit->text();

  // Add code to verify the username and password here

  if (!username.isEmpty() && !password.isEmpty()) {
    // Add code to show the main window or do other tasks here
    log("Login attempted:", "#FF0000");
    log("\tusername: "+username, "#FF0000");
    log("\tpassword: "+password, "#FF0000");
  } else {
    QMessageBox::warning(this, "Error", "Incorrect username or password");
  }
}
LoginWidget::~LoginWidget() {

}
