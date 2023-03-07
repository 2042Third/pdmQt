#ifndef PDMRUNTIME_H
#define PDMRUNTIME_H

#include <QObject>
#include <src/handler/pdm_database.h>
#include <src/handler/pdm_status.h>
#include <src/handler/pdm_net.h>


  class PdmRunTime : public QObject,
      public PDM::Status,
      public PDM::network {

  Q_OBJECT
  public:

    PDM::pdm_database * db; // debug
    PDM::pdm_database * user_conf; // User config
    PDM::pdm_database * user_data; // User data
    explicit PdmRunTime(QObject *parent = nullptr);
    ~PdmRunTime();
    std::string conf_loc;
    std::string data_loc;

    int signin_action(const std::string&a, NetWriter* wt_in,const char* password,const char* email);
    int signin_action(const std::string&a, NetWriter* wt_in,const char* password,const char* email,
                      size_t _callback(char *, size_t , size_t , void *));
    int get_user_loc(const std::string &file_names,int conf=1);

    void on_loginSuccess(const NetObj* netObj);
    void on_loginFail(const NetObj* netObj);
  signals:
    void log(const QString &message, const QString &color);
    void loginSuccess(const NetObj* netObj);
    void loginFail(const NetObj* netObj);

  };
#endif // PDMRUNTIME_H
