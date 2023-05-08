#ifndef PDMRUNTIME_H
#define PDMRUNTIME_H

#include <QObject>
#include "src/handler/db/pdm_database.h"
#include <src/handler/pdm_status.h>
#include <src/handler/pdm_net.h>
#include "handler/pdm_settings.h"
#include "handler/dao/pdmLocalDao.h"
#include "handler/dao/pdmNotesCache.h"


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

  // Data Handlers
  QString currentStatusBar ;
  void userDataCheck();

public slots:
  void on_loginSuccess();
  void on_loginFail();

  signals:
  void log(const QString &message, const QString &color);

  void loginSuccess();
  void loginFail();
  void noteHeadsSuccess();
  void noteHeadsFail();
  void noteRetrieveSuccess();
  void noteRetrieveFail();
  void databaseLocalReady();
  void noteListLeftClicked(const QModelIndex &index);
  void noteListRightClicked(const QModelIndex &index);

  };
#endif // PDMRUNTIME_H
