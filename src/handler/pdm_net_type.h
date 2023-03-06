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
    static std::map<std::string,std::string>get_signin_json(const char* email, const char* password);
    static std::map<std::string,std::string>get_note_heads(const std::string&sess, const std::string&email, const std::string& ntype);
  };
}

#endif //PDM_PLATFORMS_UI_PDM_NET_TYPE_H
