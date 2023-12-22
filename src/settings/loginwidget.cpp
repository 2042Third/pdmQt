/**
 * By Yi Yang
 *  Feb. 2023
 * */

#include "loginwidget.h"
#include "handler/pdm_net_type.h"
#include "misc/md5.h"
#include <QFormLayout>
#include <QKeyEvent>

LoginWidget::LoginWidget(QWidget *parent, PdmRunTime *rtIn)
    : QWidget(parent), PdmRunTimeRef(rtIn)
{
  m_emailEdit = new QLineEdit(this);
  m_passwordEdit = new QLineEdit(this);
  m_passwordEdit->setEchoMode(QLineEdit::Password);

  m_loginButton = new QPushButton("Login", this);
  connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
  // Install event filter to catch Enter key press
  m_emailEdit->installEventFilter(this);
  m_passwordEdit->installEventFilter(this);
  m_emailEdit->setPlaceholderText("Enter your email");
  m_passwordEdit->setPlaceholderText("Enter your password");
  m_emailEdit->setFocus();

  QFormLayout *formLayout = new QFormLayout(this);
  formLayout->addRow("Email:", m_emailEdit);
  formLayout->addRow("Password:", m_passwordEdit);
  formLayout->addRow(m_loginButton);

  setLayout(formLayout);

  std::unique_ptr<PDM::Local> tmp = rt->local_dao->find_by_key("StoredLoginEmail");
  if (tmp) {
    m_emailEdit->setText(QString::fromStdString(tmp->val.val));
  }
}
void LoginWidget::onLoginClicked()
{
  static std::string j_str;
  QString username = m_emailEdit->text();
  QString password = m_passwordEdit->text();


  if (!username.isEmpty() && !password.isEmpty()) {
    emit rt->log("Login attempted:", "#FF0000");
    emit rt->log("\tusername: "+username, "#FF0000");
    emit rt->log("\tpassword: "+password, "#FF0000");
    // Get JSON object of the user login information
    std::map<std::string,std::string> data= PDM::pdm_net_type::getSigninJsonStr(username.toUtf8().constData(),
                                                                                password.toUtf8().constData());
    j_str = PDM::network::get_json(data);
    rt->signin_action(j_str, &rt->wt,password.toUtf8().constData(), username.toUtf8().constData(),
                      PdmRunTime::SigninNetCallBack_::_callback);
    emit rt->log("Login send to the server ...", "#016C05");

  } else {
    QMessageBox::warning(this, "Error", "No username or password");
    emit rt->log("Error", "#FF0004");
    emit rt->log("username or password not entered.", "#FF0004");
  }
}

bool LoginWidget::eventFilter(QObject *object, QEvent *event) {
  // Catch Enter key press events and trigger login button click
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
      onLoginClicked();
      return true;
    }
  }
  return QObject::eventFilter(object, event);
}

LoginWidget::~LoginWidget() {

}
