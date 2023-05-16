#include "PdmRunTime.h"
#include "misc/md5.h"
#include "empp.h"
#include "handler/pdm_qt_helpers.h"
#include "others/PasswordDialog.h"
#include "mainwindow.h"
#include "handler/pdm_net_type.h"
#include <QObject>
#include <QMessageBox>

PdmRunTime::PdmRunTime(QObject *parent)
      : QObject(parent) {
  db = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  app_settings = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  local_dao = new PDM::LocalDao(); // Create the db that stores the configurations
  user_conf = new PDM::pdm_database(); // Create config db for user
  user_data = new PDM::pdmNotesCache(); // Create config db for user

  set_db(user_data); // User local data.
//  set_db(db); // Old

  // Slots
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
    conf_loc = std::filesystem::absolute( std::filesystem::path(conf_loc)).string();
    const std::filesystem::path confp(conf_loc);
    return std::filesystem::exists(confp);
  }
  else if (conf == 0) {
    data_loc = "./user/" + file_names + "/data/" + file_names + ".data";
    data_loc = std::filesystem::absolute( std::filesystem::path(data_loc)).string();
    const std::filesystem::path datap(data_loc);
    return std::filesystem::exists(datap);
  }
  return 0;
}


void PdmRunTime::on_loginSuccess() {
  emit log(("Login successful: "+wt.userinfo.email).c_str(), "#00CC00");
  // Decrypt the user's data and store it in the runtime.
  // This should be the first thing to do after login
  userDataCheck();

}

void PdmRunTime::on_loginFail() {
  emit log(("Login Failed for \""+wt.userinfo.email
                +"\", status: "+ wt.userinfo.status).c_str(), "#FF0004");
  QMessageBox msgBox;
  msgBox.setWindowTitle("Login Failed");
  msgBox.setText("Login Failed");
  msgBox.setInformativeText(("Email or password incorrect. Please try again."
                             " Status: "+ wt.userinfo.status).c_str());
  msgBox.setStyleSheet("QLabel{min-width: 300px; color: red;}");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.setDefaultButton(QMessageBox::Ok);
  msgBox.exec();
}

PdmRunTime::~PdmRunTime() {
  delete db;
  delete app_settings;
  delete local_dao;
  delete user_data;
  delete user_conf;
}

int PdmRunTime::signin_action(const std::string &a, NetWriter *wt_in, const char *password, const char *email,
                              size_t (*_callback)(char *, size_t, size_t, void *)) {
  std::string ps = password, user_mail = email;
  std::cout<<"User email: "<< wt.userinfo.email<< std::endl;
  MD5 md5; md5.add(user_mail.c_str(),user_mail.size());
  std::string file_names = md5.getHash();
  get_user_loc(file_names); // Get user's database location
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
  local_dao->insert("StoredLoginEmail",wt.userinfo.email);
  PasswordDialog dialog;
  dialog.setRef(this);
  dialog.adjustSize();
  dialog.move(((MainWindow*)main_window)->geometry().center() - dialog.geometry().center());
  if (dialog.exec() == QDialog::Accepted) {
    local_dao->insert("email/"+wt.userinfo.email, loader_check(wt.app_ps,wt.data));
  } else {
    local_dao->insert("email/"+wt.userinfo.email, loader_check(wt.app_ps,wt.data));
  }
  std::unique_ptr<PDM::Local> tmp = local_dao->find_by_key("StoredLoginEmail"); // Find data for local app configurations
  emit log(("StoredLoginEmail: "+(tmp?tmp->val.val:"null")).c_str(), "#00CC00");
  std::unique_ptr<PDM::Local> tmp1 = local_dao->find_by_key("email/"+wt.userinfo.email); // Find data for local app configurations
  emit log(("email/"+wt.userinfo.email+": "+(tmp1?tmp1->val.val:"null")).c_str(), "#00CC00");
}

int PdmRunTime::setup_settings_check() {
  const std::filesystem::path setting_path("./settings/settings");
  return std::filesystem::exists(setting_path);
}

int PdmRunTime::setup_settings() {
  app_settings->open_db("./settings/settings","pdmnotes",8); // Make local user configurations
  local_dao->open_db("./conf/conf","pdmnotes",8); // Make local app configurations
  local_dao->create_table(); // Create table for local app configurations
  local_dao->insert("LoginAttampt", "DEBUG"); // Insert data for local app configurations

  std::unique_ptr<PDM::Local> tmp = local_dao->find_by_key("LoginAttampt"); // Find data for local app configurations
  emit log(("LoginAttampt: "+(tmp?tmp->val.val:"null")).c_str(), "#00CC00");
  return 0;
}

void PdmRunTime::checkExistingUser() {
  std::unique_ptr<PDM::Local> email = local_dao->find_by_key("StoredLoginEmail");
  if (email) {
    std::unique_ptr<PDM::Local> encd_ps = local_dao->find_by_key("email/"+email->val.val);
    if (!encd_ps) {
      emit log("No password found for stored account", "#FF0004");
      return;
    }
    // Ask for the decryption password
    PasswordDialog dialog;
    dialog.setRef(this);
    dialog.mTitle = "Decrypt your data";
    dialog.mLabel = "Enter decryption password for stored account "
                    + QString::fromStdString(email->val.val) + ": ";
    dialog.setLabel(dialog.mLabel);
    dialog.adjustSize();
    dialog.move(((MainWindow*)main_window)->geometry().center() - dialog.geometry().center());
    if (dialog.exec() == QDialog::Accepted) {
      std::string ps = loader_out(wt.app_ps,encd_ps->val.val);
      if (!ps.size()) {
        emit log("Password decryption failed", "#FF0004");
        return;
      }
      std::map<std::string,std::string>
          data= PDM::pdm_net_type::getSigninJsonStr(email->val.val.c_str(),ps.c_str());
      std::string j_str = PDM::network::get_json(data);
      signin_action(j_str,&wt,ps.c_str(),email->val.val.c_str(),SigninNetCallBack_::_callback);
      emit log("Existing login send to the server ...", "#016C05");
    } else {
      emit log("Existing login failed to send to the server ...", "#016C05");
    }
  }
}
