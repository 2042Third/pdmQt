#include "PdmRunTime.h"
#include "misc/md5.h"
#include "empp.h"
#include "handler/pdm_qt_helpers.h"
#include <QObject>
#include <QMessageBox>

PdmRunTime::PdmRunTime(QObject *parent)
      : QObject(parent) {
  db = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  app_settings = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  local_dao = new PDM::LocalDao(); // Create the db that stores the configurations
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
}

int PdmRunTime::setup_settings_check() {
  const std::filesystem::path setting_path("./settings/settings");
  return std::filesystem::exists(setting_path);
}

int PdmRunTime::setup_settings() {
//  if(setup_settings_check()){
//    emit log("Settings already exist", "#FF0004");
//    return 1;
//  }
//  emit log("Creating settings", "#00CC00");
  app_settings->open_db("./settings/settings","pdmnotes",8); // Make local user configurations
  local_dao->open_db("./conf/conf","pdmnotes",8); // Make local app configurations
//  local_dao->create_table(); // Create table for local app configurations
  return 0;
}