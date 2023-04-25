/**
 * By Yi Yang
 *  Feb. 2023
 * */

#include "loginwidget.h"
#include "handler/pdm_net_type.h"
#include "misc/md5.h"
#include <QFormLayout>
#include <QKeyEvent>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent),PdmRuntimeRef()
{
  m_emailEdit = new QLineEdit(this);
  m_passwordEdit = new QLineEdit(this);
  m_passwordEdit->setEchoMode(QLineEdit::Password);

  m_loginButton = new QPushButton("Login", this);
  connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
  // Install event filter to catch Enter key press
  m_emailEdit->installEventFilter(this);
  m_passwordEdit->installEventFilter(this);

  QFormLayout *formLayout = new QFormLayout(this);
  formLayout->addRow("Email:", m_emailEdit);
  formLayout->addRow("Password:", m_passwordEdit);
  formLayout->addRow(m_loginButton);

  setLayout(formLayout);
}
void LoginWidget::onLoginClicked()
{
  static std::string j_str;
  QString username = m_emailEdit->text();
  QString password = m_passwordEdit->text();

  // Call back
  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) PDM::network::post_callback_signin(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      emit rt->log("Callback started and successful ("+QString(wt->js.dump().c_str())+")", "#016C05");
      if (rt->wt.userinfo.status == "success") { // The sign in is successful
        MD5 md5; md5.add(wt->userinfo.email.c_str(),wt->userinfo.email.size());
        std::string file_names = md5.getHash(); // md5 encode user email
        // Check or create the appropriate db
        if (!rt->get_user_loc(file_names,0)){
          const std::filesystem::path confp(rt->conf_loc), datap(rt->data_loc);
          std::filesystem::create_directories(datap.parent_path()); // Create user data dir.
          rt->user_conf->execute(rt->user_conf->local_table_create_query); // Make user config table when not exist
          emit rt->log("made user config table", "#016C05");
        }
        else {
          emit rt->log("User config file found", "#016C05");
        }
        rt->user_data->open_db(rt->data_loc.c_str(),wt->data.c_str(),wt->data.size()); // Always new user data

        emit rt->log("Databse location: ", "#016C05");
        emit rt->log(rt->conf_loc.c_str() , "#016C05");

        emit rt->log(" Database opened!", "#016C05");
        emit rt->loginSuccess();
      } else {
        emit rt->log("Unsuccessful callback. ", "#6C2501");
        emit rt->loginFail();
      }
      return callback_out; /* we copied this many bytes */
    }
  };

  // Add code to verify the username and password here

  if (!username.isEmpty() && !password.isEmpty()) {
    emit rt->log("Login attempted:", "#FF0000");
    emit rt->log("\tusername: "+username, "#FF0000");
    emit rt->log("\tpassword: "+password, "#FF0000");
    // Get JSON object of the user login information
    std::map<std::string,std::string> data=PDM::pdm_net_type::get_signin_json(username.toUtf8().constData(),password.toUtf8().constData());
    j_str = PDM::network::get_json(data);
    rt->signin_action(j_str, &rt->wt,password.toUtf8().constData(), username.toUtf8().constData(),
                      NetCallBack_::_callback);
    emit rt->log("Login send to the server ...", "#016C05");

  } else {
    QMessageBox::warning(this, "Error", "Incorrect username or password");
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