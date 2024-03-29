//
// Created by Yi Yang on 12/13/2022.
//

#ifndef PDM_PLATFORMS_UI_PDM_NET_H
#define PDM_PLATFORMS_UI_PDM_NET_H

#include <string>
#include "nlohmann/json.hpp"
#include <map>
#include "pdm-network.h"
#include "types.h"
#include "src/handler/db/pdm_database.h"

struct NetObj:NetWriter {
  std::string readptr;
  size_t sizeleft;
  nlohmann::json js;
  PDM::UserInfo userinfo;
  PDM::pdm_database * db;
  std::string app_ps;
};
namespace PDM {

  class network {
    using json = nlohmann::json;
  public:
    struct _notes{
      const std::string GetHeadsType = "heads";
      const std::string GetNoteType = "retrieve";
      const std::string GetNewNoteType = "new";
      const std::string UpdateNoteType = "update";
      const std::string DeleteNoteType = "delete";
    };
    struct _actions {
      const std::string pdmRootURL = "https://pdm.pw";
      const std::string signinURL = pdmRootURL+"/auth/signin";
      const std::string signupURL = pdmRootURL + "/auth/signup";
      const std::string notesGetHeadsURL = pdmRootURL + "/auth/note";
      const std::string notesHeaderURL = pdmRootURL + "/auth/note";
    };


    static void post (const std::string& a, const std::string& b, NetWriter* wt,size_t callback(char *,size_t,size_t,void *));
    template<typename T>
    static std::string get_json (std::map<T,T>&a) {
      json j(a);
      std::string signin_data =to_string(j);
      return std::move(signin_data);
    }

    static int signin_post       (const std::string&a, NetWriter* wt_in,
                           size_t _callback(char *, size_t , size_t , void *)=post_callback_signin );

    static void get_userinfo (const json &j,UserInfo& userinfo);
    static size_t post_callback_heads( char *data, size_t size, size_t nmemb, void *userp);
    static size_t post_callback_note( char *data, size_t size, size_t nmemb, void *userp);
    static size_t post_callback_signin( char *data, size_t size, size_t nmemb, void *userp);
    static size_t post_callback_update( char *data, size_t size, size_t nmemb, void *userp);
    static size_t post_callback_new( char *data, size_t size, size_t nmemb, void *userp);

    network();
    ~network();

    void set_db (pdm_database * a){wt.db = a;}

    static const _actions actions;
    static const _notes notes;
    struct NetObj wt; // store the most recent network return callback
  private:

//    pdm_network net;
  };

} // PDM

#endif //PDM_PLATFORMS_UI_PDM_NET_H
