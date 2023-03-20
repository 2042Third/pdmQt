#include "PdmRunTime.h"
#include "misc/md5.h"
#include "empp.h"
#include "handler/pdm_qt_helpers.h"
#include <QObject>
#include <QMessageBox>

PdmRunTime::PdmRunTime(QObject *parent)
      : QObject(parent) {
  db = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  user_conf = new PDM::pdm_database(); // Create config db for user
  user_data = new PDM::pdm_database(); // Create config db for user

  set_db(db);

  connect (this, &PdmRunTime::loginSuccess, this, &PdmRunTime::on_loginSuccess);
  connect (this, &PdmRunTime::loginFail, this, &PdmRunTime::on_loginFail);
}
/**
   * Checks if user exists on this computer.
   * Locations:
   *    "./user/${file_names}/${file_names}"
   *    "./user/${file_names}/data/${file_names}.data"
   * @params conf - configuration, default 1; 1 = user configuration, else user data configuration
   * */
int PdmRunTime::get_user_loc (const std::string& file_names,int conf) {
  if (conf == 1 ) {
    conf_loc = "./user/" + file_names + "/" + file_names;
    const std::filesystem::path confp(conf_loc);
    return std::filesystem::exists(confp);
  }
  else if (conf == 0) {
    data_loc = "./user/" + file_names + "/data/" + file_names + ".data";
    const std::filesystem::path datap(data_loc);
    return std::filesystem::exists(datap);
  }
  return 0;
}

int PdmRunTime::signin_action(const std::string &a, NetWriter *wt_in, const char *password, const char *email) {
  std::string ps = password, user_mail = email;
  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) post_callback_signin(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      if (rt->wt.userinfo.status == "success") { // The sign in is successful
        MD5 md5; md5.add(wt->userinfo.email.c_str(),wt->userinfo.email.size());
        std::string file_names = md5.getHash(); // md5 encode user email
        // Check or create the appropriate db
        if (!rt->get_user_loc(file_names,0)){
          const std::filesystem::path confp(rt->conf_loc), datap(rt->data_loc);
          std::filesystem::create_directories(datap.parent_path()); // Create user data dir.
          // TODO: What to do when user first use this computer to login
        }
        std::cout<< "data_loc: "<< rt->data_loc<<std::endl;
        rt->user_data->open_db(rt->data_loc.c_str(),wt->data.c_str(),wt->data.size());
      } else {
        std::cout<< "Unsuccessful callback."<<std::endl;
        // TODO: Deal with the failed login
      }
      return callback_out; /* we copied this many bytes */
    }
  };
  std::cout<<"User email: "<< wt.userinfo.email<< std::endl;
  MD5 md5; md5.add(user_mail.c_str(),user_mail.size());
  std::string file_names = md5.getHash();
  get_user_loc(file_names);
  const std::filesystem::path confp(conf_loc);
  std::filesystem::create_directories(confp.parent_path()); // Create user config dir
  std::cout<< "conf_loc: "<< conf_loc<<std::endl;
  user_conf->open_db(conf_loc.c_str(),"pdmnotes",8); // Make local user configurations
  wt_in->pdm_runtime = this;
  wt_in->data = ps;
  signin_post(a,wt_in,NetCallBack_::_callback); // Call network post for Sign In action

  return 1;
}
void PdmRunTime::on_loginSuccess() {
  emit log(("Login successful: "+wt.userinfo.email).c_str(), "#00CC00");

}

void PdmRunTime::on_loginFail() {
  emit log(("Login Failed for \""+wt.userinfo.email
                +"\", status: "+ wt.userinfo.status).c_str(), "#FF0004");
  // Show a window to tell the user that the login failed with the reason.
  QMessageBox msgBox;
  msgBox.setWindowTitle("Login Failed");
  msgBox.setText("Login Failed");
  msgBox.setInformativeText(("Email or password incorrect. Please try again."
                             " Status: "+ wt.userinfo.status).c_str());
  // Message with red text
  msgBox.setStyleSheet("QLabel{min-width: 300px; color: red;}");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setDefaultButton(QMessageBox::Ok);
  msgBox.exec();

}

PdmRunTime::~PdmRunTime() {

  delete db;
  delete user_data;
  delete user_conf;
}

int PdmRunTime::signin_action(const std::string &a, NetWriter *wt_in, const char *password, const char *email,
                              size_t (*_callback)(char *, size_t, size_t, void *)) {
  std::string ps = password, user_mail = email;
  std::cout<<"User email: "<< wt.userinfo.email<< std::endl;
  MD5 md5; md5.add(user_mail.c_str(),user_mail.size());
  std::string file_names = md5.getHash();
  get_user_loc(file_names);
  const std::filesystem::path confp(conf_loc);
  std::filesystem::create_directories(confp.parent_path()); // Create user config dir
  std::cout<< "conf_loc: "<< conf_loc<<std::endl;
  user_conf->open_db(conf_loc.c_str(),"pdmnotes",8); // Make local user configurations
  wt_in->pdm_runtime = this;
  wt_in->data = ps;
  signin_post(a,wt_in,_callback); // Call network post for Sign In action

  return 1;
}

void PdmRunTime::userDataCheck() {
  wt.userinfo.username = loader_out(wt.data,wt.userinfo.receiverstring); // username decryption
  wt.userinfo.ctime = PDM::pdm_qt_helpers::unix_time_to_qstr(wt.userinfo.time).toStdString(); // date time string
}
