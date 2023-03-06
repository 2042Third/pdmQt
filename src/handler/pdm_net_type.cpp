//
// Created by Yi Yang on 12/19/2022.
//

#include "pdm_net_type.h"
#include "empp.h"

namespace PDM {


  std::map<std::string,std::string> pdm_net_type::get_signin_json(const char* email, const char* password){
    std::string ps = password,user_mail = email;
     std::map<std::string,std::string> data
     {
        {"umail", email           }
       ,{"upw"  , get_hash(ps+ps) } // make the server-side password hash
     };
     return std::move(data);
  }

  std::map<std::string, std::string> pdm_net_type::get_note_heads(const std::string&sess,
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

}