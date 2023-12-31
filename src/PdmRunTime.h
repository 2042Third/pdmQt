#ifndef PDMRUNTIME_H
#define PDMRUNTIME_H


#include <QObject>
#include "src/handler/db/pdm_database.h"
#include <src/handler/pdm_status.h>
#include <src/handler/pdm_net.h>
#include "handler/pdm_settings.h"
#include "handler/dao/pdmLocalDao.h"
#include "handler/dao/pdmNotesCache.h"
#include "misc/md5.h"
#include "handler/pdm_status_qt.h"
class NotesScroll;

class PdmRunTime : public QObject,
  public PDM::Status,
  public PDM::network,
  public PDM::Settings{

Q_OBJECT

public:

  PDM::pdm_database * db; // debug
  PDM::pdm_database * app_settings; // Settings
  PDM::LocalDao * local_dao; // Local Dao
  PDM::pdm_database * user_conf; // User config
  PDM::pdmNotesCache * user_data; // User data
  NotesScroll* noteList;
  StatusQt* statusQt;
explicit PdmRunTime(QObject *parent = nullptr);
  ~PdmRunTime();
  std::string conf_loc;
  std::string data_loc;

  // Actions
  int signin_action(const std::string&a, NetWriter* wt_in,const char* password,const char* email,
                  size_t _callback(char *, size_t , size_t , void *));
  int get_user_loc(const std::string &file_names,int conf=1);
  int setup_settings();
  static int setup_settings_check();
  void checkExistingUser();
  static void toggleAnimation(PdmRunTime *rt, int state) ;
  static void changeAnimationSpeed(PdmRunTime* rt, int value) ;
  int getCmd(const std::string &cmd);
  void setCmd(const std::string &cmd, double value);
  void setCmd(const std::string &cmd, int value);
  int runCmd(const std::string &cmd);

  void showPendingAnimation();
  void showSaveCompleteAnimation();

  // Data Handlers
  QString currentStatusBar ;
  void userDataCheck();
  int isLoginSuccessful() const;

  // Refs
  void * main_window;

  // Windowing States
  bool debugWindowFocusedState = false;
  bool mainWindowFocusedState = false;
public:
  int isClosing=0;

public slots:
  void on_loginSuccess();
  void on_loginFail();
  void on_statusChanged(const QString &status);

  signals:
  void log(const QString &message, const QString &color);
  void logc(const QString &message, const QString &color);
  void log_std(const std::string &message, const std::string &color);
  void logc_std(const std::string &message, const std::string &color);
  void loginSuccess();
  void loginFail();
  // Notes
  void noteHeadsSuccess();
  void noteHeadsFail();
  void noteRetrieveSuccess(int noteid);
  void noteRetrieveFail(int noteid);
  void noteCreateSuccess();
  void noteCreateFail();
  void noteUpdateSuccess(int noteid);
  void noteUpdateFail(int noteid);
  void noteDeleteSuccess(int noteid);
  void noteDeleteFail(int noteid);
  void databaseLocalReady();
  void noteRename(int noteId);
  // Note List
  void noteListLeftClicked(const QModelIndex &index);
  void noteListRightClicked(const QModelIndex &index);
  void onZoomIn();
  void onZoomOut();
  // Debug Window
  void debugWindowFocused();
  void debugWindowBlurred();
  // Main Window
  void mainWindowFocused();
  void mainWindowBlured();
private:
    int hasLogIn = 0;


public: // network callbacks
  // Call back
  struct SigninNetCallBack_ {
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
        rt->user_data->execute(rt->user_data-> note_table_create_query); // Make user data table when not exist

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

    void changeMainwindowStatusColor(const QString &txt) const;

  void setupCommands();

  void updateNoteContent(int noteid, std::string content) ;

  void updateNoteToServer(int noteid);
};
#endif // PDMRUNTIME_H
