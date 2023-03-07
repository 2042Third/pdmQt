#include "loginwidget.h"
#include "handler/pdm_net_type.h"
#include "misc/md5.h"
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

  // Call back
  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) PDM::network::post_callback_signin(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      emit rt->log("Callback started and successful", "#016C05");
      if (rt->wt.userinfo.status == "success") { // The sign in is successful
        MD5 md5; md5.add(wt->userinfo.email.c_str(),wt->userinfo.email.size());
        std::string file_names = md5.getHash(); // md5 encode user email
        // Check or create the appropriate db
        if (!rt->get_user_loc(file_names,0)){
          const std::filesystem::path confp(rt->conf_loc), datap(rt->data_loc);
          std::filesystem::create_directories(datap.parent_path()); // Create user data dir.
          // TODO: What to do when user first use this computer to login
        }
        emit rt->log((" \"data_loc: \""+rt->data_loc).c_str(), "#016C05");
        rt->user_data->open_db(rt->data_loc.c_str(),wt->data.c_str(),wt->data.size());
        emit rt->log(" Database opened!", "#016C05");
      } else {
        emit rt->log("Unsuccessful callback. ", "#6C2501");
        // TODO: Deal with the failed login
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
    rt->signin_action(j_str, &rt->wt,password.toUtf8().constData(), username.toUtf8().constData());
    emit rt->log("Login send to the server ...", "#016C05");

  } else {
    QMessageBox::warning(this, "Error", "Incorrect username or password");
    emit rt->log("Error", "#FF0004");
    emit rt->log("username or password not entered.", "#FF0004");
  }
}
LoginWidget::~LoginWidget() {

}
