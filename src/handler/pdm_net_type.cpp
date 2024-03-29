//
// Created by Yi Yang on 12/19/2022.
//

#include "pdm_net_type.h"
#include "empp.h"

namespace PDM {


  std::map<std::string,std::string> pdm_net_type::getSigninJsonStr(const char* email, const char* password){
    std::string ps = password,user_mail = email;
     std::map<std::string,std::string> data
     {
        {"umail", email           }
       ,{"upw"  , get_hash(ps+ps) } // make the server-side password hash
     };
     return std::move(data);
  }

  std::map<std::string, std::string> pdm_net_type::getNoteHeadsJsonStr(const std::string&sess,
                                                                       const std::string&email,
                                                                       const std::string& ntype) {
    std::map<std::string,std::string> data
        {
             {"username" , "" }
            ,{"content"  , "" }
            ,{"sess"     , sess } // use the stored session key for encryption
            ,{"ntype"    , ntype }
            ,{"email"    , email }
        };
    return std::move(data);
  }
  std::map<std::string, std::string> pdm_net_type::getNoteRetrieveJsonStr(const std::string&sess,
                                                                          const std::string&email,
                                                                          const std::string&noteId,
                                                                          const std::string& ntype) {
    std::map<std::string,std::string> data
        {
             {"username" , "" }
            ,{"content"  , "" }
            ,{"sess"     , sess } // use the stored session key for encryption
            ,{"ntype"    , ntype }
            ,{"email"    , email }
            ,{"note_id"  , noteId}
        };
    return std::move(data);
  }
  std::map<std::string, std::string> pdm_net_type::getNoteUpdateJsonStr(const std::string&sess,
                                                                          const std::string&email,
                                                                          const std::string&noteId,
                                                                          const std::string& ntype,
                                                                          const std::string& head,
                                                                           const std::string& content
                                                                           ,const std::string& h) {
    std::map<std::string,std::string> data
        {
             {"username" , "" }
            , {"head", head}
            ,{"content"  , content }
            ,{"sess"     , sess } // use the stored session key for encryption
            ,{"ntype"    , ntype }
            ,{"email"    , email }
            ,{"note_id"  , noteId}
            , {"h", h}
        };
    return std::move(data);
  }

  std::map<std::string, std::string>
  pdm_net_type::getNoteNewJsonStr(const std::string &sess, const std::string &email, const std::string &ntype) {
    std::map<std::string,std::string> data
        {
             {"username" , "" }
            ,{"content"  , "" }
            ,{"sess"     , sess } // use the stored session key for encryption
            ,{"ntype"    , ntype }
            ,{"email"    , email }
        };
    return std::move(data);
  }

}