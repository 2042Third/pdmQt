#include "loginwidget.h"
#include "handler/pdm_net_type.h"
#include <QFormLayout>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent),PdmRuntimeRef()
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
  static std::string j_str;
  QString username = m_usernameEdit->text();
  QString password = m_passwordEdit->text();

  // Add code to verify the username and password here

  if (!username.isEmpty() && !password.isEmpty()) {
    emit rt->log("Login attempted:", "#FF0000");
    emit rt->log("\tusername: "+username, "#FF0000");
    emit rt->log("\tpassword: "+password, "#FF0000");
    // Get JSON object of the user login information
    std::map<std::string,std::string> data=PDM::pdm_net_type::get_signin_json(username.toUtf8().constData(),password.toUtf8().constData());
    j_str = PDM::network::get_json(data);
    rt->signin_action(j_str, &rt->wt,password.toUtf8().constData(), username.toUtf8().constData());
    emit rt->log("Login send to the server ...", "#D6FC19");

  } else {
    QMessageBox::warning(this, "Error", "Incorrect username or password");
    emit rt->log("Error", "#FF0004");
    emit rt->log("username or password not entered.", "#FF0004");
  }
}
LoginWidget::~LoginWidget() {

}
