#include "PdmRunTime.h"
#include "misc/md5.h"
#include "empp.h"
#include "handler/pdm_qt_helpers.h"
#include "others/PasswordDialog.h"
#include "mainwindow.h"
#include "handler/pdm_net_type.h"
#include "helpers/FlashingCircle.h"
#include "handler/pdm_status_qt.h"
#include "helpers/Animated.h"
#include "handler/pdmqt/pdm_qt_net.h"
#include <QObject>
#include <QMessageBox>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrent>

#define PdmRunTime_SETTING_STRING_EMITTER_BLUE(x) \
  emit log((std::string(#x "=")+std::to_string(x)).c_str(), "#0000FF");


PdmRunTime::PdmRunTime(QObject *parent)
      : QObject(parent),
        PDM::Settings() {
  db = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  app_settings = new PDM::pdm_database(); // Create the db used for debug, also store the most recent data
  local_dao = new PDM::LocalDao(); // Create the db that stores the configurations
  user_conf = new PDM::pdm_database(); // Create config db for user
  user_data = new PDM::pdmNotesCache(); // Create config db for user
  statusQt = new StatusQt();

  set_db(user_data); // User local data.

  // Initial states
  this->hasLogIn = 0;

  // Slots
  connect (this, &PdmRunTime::loginSuccess, this, &PdmRunTime::on_loginSuccess);
  connect (this, &PdmRunTime::loginFail, this, &PdmRunTime::on_loginFail);

  // Commands
  setupCommands();
}
/**
   * Checks if user exists on this computer.
   * Locations:
   *    "./user/${file_names}/${file_names}"
   *    "./user/${file_names}/data/${file_names}.data"
   * @params conf - configuration, default 1; 1 = user configuration, else user data configuration
   * */
int PdmRunTime::get_user_loc (const std::string& file_names,int conf) {
  QString path;
  if (conf == 1) {
    path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    conf_loc = path.toStdString() + "/user/" + file_names + "/" + file_names;
    const std::filesystem::path confp(conf_loc);
    return std::filesystem::exists(confp);
  }
  else if (conf == 0) {
    path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    data_loc = path.toStdString() + "/user/" + file_names + "/data/" + file_names + ".data";
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
  this->hasLogIn = 1;

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
  delete statusQt;
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
  QtConcurrent::run(signin_post,a,wt_in,_callback); // Call network post for Sign In action

  return 1;
}

void PdmRunTime::userDataCheck() {
  wt.userinfo.username = loader_out(wt.data,wt.userinfo.receiverstring); // username decryption
  wt.userinfo.ctime = PDM::pdm_qt_helpers::unix_time_to_qstr(wt.userinfo.time).toStdString(); // date time string
  local_dao->insert("StoredLoginEmail",wt.userinfo.email);
  PasswordDialog dialog(nullptr,this);
  dialog.adjustSize();
  dialog.move(((MainWindow*)main_window)->geometry().center() - dialog.geometry().center());

  std::unique_ptr<PDM::Local> out = local_dao->find_by_key("hasAppPs/"+wt.userinfo.email); // Check if user has app password

  if(out == nullptr){
    if (dialog.exec() == QDialog::Accepted) {
      emit log("Setting app password: " + QString::fromStdString(wt.app_ps), "#00CC00");
      local_dao->insert("email/" + wt.userinfo.email, loader_check(wt.app_ps, wt.data));
      MD5 md5;
      md5.add(wt.userinfo.email.c_str(), wt.userinfo.email.size());
      std::string emailVer = md5.getHash(); // md5 encode user email
      local_dao->insert("email/" + wt.userinfo.email + "/verify", loader_check(wt.app_ps, emailVer));
      local_dao->insert("hasAppPs/" + wt.userinfo.email, "1");

    } else {
      local_dao->insert("email/" + wt.userinfo.email, loader_check(wt.app_ps, wt.data));
    }
  }
  else {
    emit log("Application found password","#000000");
    emit log("App password: "+ QString::fromStdString(wt.app_ps), "#00CC00");
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
  QString path;
  path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
  std::string stdPath = path.toStdString() +"/settings/settings";
  app_settings->open_db(stdPath.c_str(),"pdmnotes",8); // Make local user configurations
  stdPath = path.toStdString() +"/conf/conf";
  local_dao->open_db(stdPath.c_str(),"pdmnotes",8); // Make local app configurations
  local_dao->create_table(); // Create table for local app configurations
  local_dao->insert("LoginAttampt", "DEBUG"); // Insert data for local app configurations

  std::unique_ptr<PDM::Local> tmp = local_dao->find_by_key("LoginAttampt"); // Find data for local app configurations
  emit log(("LoginAttampt: "+(tmp?tmp->val.val:"null")).c_str(), "#00CC00");
  return 0;
}

void PdmRunTime::checkExistingUser() {
  std::unique_ptr<PDM::Local> email = local_dao->find_by_key("StoredLoginEmail");
  if (email) { // Check if a user has logged in before
    std::unique_ptr<PDM::Local> encd_ps = local_dao->find_by_key("email/"+email->val.val);
    std::unique_ptr<PDM::Local> encd_ps_ver = local_dao->find_by_key("email/"+email->val.val+"/verify");
    if (!encd_ps) { // No local data found
      emit log("No password found for stored account", "#FF0004");
      return;
    }
    // Ask for the decryption password
    PasswordDialog dialog(nullptr,this);
    dialog.mTitle = "Decrypt your data";
    dialog.mLabel = "Found existing user data. Enter decryption password for stored account "
                    + QString::fromStdString(email->val.val) + ": ";

    if(encd_ps_ver) {

      MD5 md5; md5.add(email->val.val.c_str(),email->val.val.size());
      emit log(("email/"+email->val.val+": "+encd_ps_ver->val.val).c_str(), "#00CC00");
      std::string v = md5.getHash();
      dialog.setMD5Verification(1, encd_ps_ver->val.val,v);

    }
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
      emit log("Existing login info decrypted, sending to the server ...", "#016C05");
    } else {
      emit log("Existing login cancelled or failed to send to the server ...", "#016C05");
    }
  }
}

int PdmRunTime::isLoginSuccessful() const {
  return hasLogIn;
}

void PdmRunTime::changeMainwindowStatusColor(const QString&txt) const{
  if(isClosing) return;
  static_cast<FlashingCircle*>(static_cast<MainWindow*>(main_window)->statusCircle)
  ->setColor(txt);
}

void PdmRunTime::on_statusChanged(const QString &status) {
  if (!statusQt) return;
  switch (statusQt->statusInstance.get_current_status()) {
    case PDM::Status::NONE:
      break;
    case PDM::Status::LOADING:
      break;
    case PDM::Status::OPEN:
      break;
    case PDM::Status::CLOSED:
      break;
    case PDM::Status::ERROR_STATE:
      break;
  }
}

void PdmRunTime::toggleAnimation(PdmRunTime* rt, int state) {
  if(state){ // Animated
    if (static_cast<MainWindow *>(rt->main_window)->animation) {
      Animated::animationStart(static_cast<MainWindow *>(rt->main_window)->animation);
    }
  }
  else{ // not Animated
    if (static_cast<MainWindow *>(rt->main_window)->animation) {
      Animated::animationStop(static_cast<MainWindow *>(rt->main_window)->animation);
    }
    if(static_cast<MainWindow *>(rt->main_window)->statusCircle){
      static_cast<FlashingCircle *>(
          static_cast<MainWindow *>(rt->main_window)->statusCircle
      )->setAlpha(255);
    }
  }
}

void PdmRunTime::changeAnimationSpeed(PdmRunTime*rt, int value)  {
  if (static_cast<MainWindow *>(rt->main_window) && static_cast<MainWindow *>(rt->main_window)->animation) {
    Animated::animationDuration(value, static_cast<MainWindow *>(rt->main_window)->animation);
  }
}

void PdmRunTime::showPendingAnimation() {
  if(isClosing) return;
  changeMainwindowStatusColor("yellow");
  toggleAnimation(this, 1);
}

void PdmRunTime::showSaveCompleteAnimation() {
  if(isClosing) return;
  changeMainwindowStatusColor("lightgreen");
  toggleAnimation(this, 0);
}

void PdmRunTime::setupCommands() {
  commandMap["showUsernameInStatusBar"] = std::make_unique<PDM::pdm_command>("showUsernameInStatusBar"
      , [this](){
        if (getCmd("showUsernameInStatusBar")){
          static_cast<MainWindow*>(this->main_window)->showUsernameInStatusBar(1);
        } else {
          static_cast<MainWindow*>(this->main_window)->showUsernameInStatusBar(0);
        }
  });
  commandMap["display_main_window_x"] = std::make_unique<PDM::pdm_command>("display_main_window_x", [](){});
  commandMap["display_main_window_y"] = std::make_unique<PDM::pdm_command>("display_main_window_y", [](){});
  commandMap["display_main_window_w"] = std::make_unique<PDM::pdm_command>("display_main_window_w", [](){});
  commandMap["display_main_window_h"] = std::make_unique<PDM::pdm_command>("display_main_window_h", [](){});
  commandMap["has_database_location"] = std::make_unique<PDM::pdm_command>("has_database_location", [](){});
  commandMap["note_new_note"] = std::make_unique<PDM::pdm_command>("note_new_note", [this](){PDM::pdm_qt_net::client_action_note_create(this);});
  commandMap["note_refresh_list"] = std::make_unique<PDM::pdm_command>("note_refresh_list", [this](){PDM::pdm_qt_net::client_action_note_heads(this);});
}

int PdmRunTime::getCmd(const std::string &cmd) {
  if (commandMap.find(cmd) != commandMap.end()) {
    return commandMap[cmd]->getValue();
  }
  return 0;
}

void PdmRunTime::setCmd(const std::string &cmd, double value) {
  if (commandMap.find(cmd) != commandMap.end()) {
    commandMap[cmd]->setValue(value);
  }
}

void PdmRunTime::setCmd(const std::string &cmd, int value) {
  if (commandMap.find(cmd) != commandMap.end()) {
    commandMap[cmd]->setValue(value);
  }
}

int PdmRunTime::runCmd(const std::string &cmd) {
  if(isClosing) return 0; // Shutdown guard
  if (commandMap.find(cmd) != commandMap.end()) {
    commandMap[cmd]->execute();
    return 1;
  }
  return 0;
}

void PdmRunTime::updateNoteContent(PDM::NoteMsg msg)  {
  user_data->updateNote(atoi(msg.note_id.c_str()), msg.content);
  // Update the note through network
  emit logc_std("Updating note through network, noteid: "+std::to_string((int)(*msg.note_id.c_str())), "blue");
  PDM::pdm_qt_net::client_action_note_update(this, msg);
}
