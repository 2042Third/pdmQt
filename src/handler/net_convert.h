//
// Created by Yi Yang on 12/21/2022.
//

#ifndef PDM_PLATFORMS_UI_NET_CONVERT_H
#define PDM_PLATFORMS_UI_NET_CONVERT_H


#include <iostream>
#include "nlohmann/json.hpp"
#include "types.h"

namespace PDM {

  class net_convert {
    using json = nlohmann::json;
  public:
    static int convert(const json &j,UserInfo& userinfo);
    static int convert(const json &j,NoteHead& notehead);
    static int convert(const json &j,NoteMsg& notemsg);
    static int exists (const json& j, const std::string & a){return j.find(a) != j.end();}
    static std::string add_str (const json& j, const std::string & a);
    static uint32_t add_number (const json& j, const std::string & a);
    static std::string add_bool (const json& j, const std::string & a);
  };
}

#endif //PDM_PLATFORMS_UI_NET_CONVERT_H
