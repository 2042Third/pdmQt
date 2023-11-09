//
// Created by Yi Yang on 12/19/2022.
//

#ifndef PDM_PLATFORMS_UI_PDM_NET_TYPE_H
#define PDM_PLATFORMS_UI_PDM_NET_TYPE_H

#include <string>
#include <map>
#include "net_convert.h"

namespace PDM {

  class pdm_net_type: public net_convert {
  public:
    static std::map<std::string,std::string>
    getSigninJsonStr(const char* email, const char* password);
    static std::map<std::string,std::string>
    getNoteHeadsJsonStr(const std::string&sess, const std::string&email, const std::string& ntype);
    static std::map<std::string,std::string>
    getNoteRetrieveJsonStr(const std::string&sess, const std::string&email, const std::string&noteId, const std::string& ntype);
    static std::map<std::string,std::string>
    getNoteUpdateJsonStr(const std::string&sess, const std::string&email, const std::string&noteId, const std::string& ntype, const std::string& content,const std::string& hash);
  };
}

#endif //PDM_PLATFORMS_UI_PDM_NET_TYPE_H
