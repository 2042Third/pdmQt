//
// Created by Yi Yang on 12/21/2022.
//

#include "net_convert.h"
#include "pdm_qt_helpers.h"

namespace PDM {
  using json = nlohmann::json;
  int net_convert::convert(const json &j,UserInfo& userinfo){
    userinfo.msg                 = add_str(j,"msg");
    userinfo.username            = add_str(j,"username");
    userinfo.msgh                = add_str(j,"msgh");
    userinfo.email               = add_str(j,"email");
    userinfo.val                 = add_str(j,"val");
    userinfo.typestring          = add_str(j,"type"); // user type as typestring
    userinfo.h                   = add_str(j,"h");
    userinfo.senderstring        = add_str(j,"sender"); // using sender
    userinfo.sess                = add_str(j,"sess");
    userinfo.status              = add_str(j,"status");
    userinfo.statusInfo          = add_str(j,"statusInfo");
    userinfo.receiverstring      = add_str(j,"receiver"); // using receiver
    userinfo.authdata            = add_str(j,"authdata");
//    userinfo.time                = PDM::pdm_qt_helpers::cstrToUint64(add_str(j,"time").c_str());
    userinfo.time                = PDM::pdm_qt_helpers::strToDouble(add_str(j,"time"));
    userinfo.update_time         = PDM::pdm_qt_helpers::strToDouble(add_str(j,"update_time"));
    userinfo.utime               = add_str(j,"utime");
    userinfo.pdmSecurityVersion  = add_str(j,"pdmSecurityVersion");
    userinfo.checker             = add_str(j,"checker");
    userinfo.ctime               = add_str(j,"ctime");
    userinfo.netStatus           = add_str(j,"netStatus");
    return 1;
  }

  int net_convert::convert(const json &j, NoteMsg &notemsg) {
    notemsg.head         = add_str(j,"head");
    notemsg.note_id      = add_str(j,"note_id");
    notemsg.uid          = add_number(j,"uid");
    notemsg.time         = PDM::pdm_qt_helpers::strToDouble(add_str(j,"time"));
    notemsg.update_time  = PDM::pdm_qt_helpers::strToDouble(add_str(j,"update_time"));
    notemsg.utime        = add_str(j,"utime");
    notemsg.ctime        = add_str(j,"ctime");
    notemsg.key          = add_number(j,"key");
    notemsg.content      = add_str(j,"content");
    notemsg.email        = add_str(j,"email");
    notemsg.session      = add_str(j,"session");
    notemsg.ntype        = add_str(j,"ntype");
    notemsg.sess         = add_str(j,"sess");
    notemsg.h            = add_str(j,"h");
    notemsg.username     = add_str(j,"username");
    notemsg.status       = add_str(j,"status");
    notemsg.statusInfo   = add_str(j,"statusInfo");
    notemsg.encry        = add_str(j,"encry");
//    notemsg.hash         = add_str(j,"hash");
    return 0;
  }

  int net_convert::convert(const json &j, NoteHead &notehead) {
    notehead.head         = add_str(j,"head");
    notehead.note_id      = add_str(j,"note_id");
    notehead.uid          = add_number(j,"uid");
    notehead.time         = PDM::pdm_qt_helpers::strToDouble(add_str(j,"time"));
    notehead.update_time  = PDM::pdm_qt_helpers::strToDouble(add_str(j,"update_time"));
    notehead.utime        = add_str(j,"utime");
    notehead.ctime        = add_str(j,"ctime");
    notehead.key          = add_number(j,"key");
    return 0;
  }

  double net_convert::add_double(const json &j, const std::string &a) {
    try {
      if (exists(j, a)) {
//        std::cout<<"Adding double: "<<a<<" as "<< j[a]<<std::endl;
        if (!j[a].is_null()) {
          return j[a].get<double>();
        }
      }
    }  catch (int err) {
      std::cout<<"[ERROR] Adding double: "<<a<<" as "<< j[a]<<std::endl;
      return -1;
    }
    return -1;
  }

  uint64_t net_convert::add_number(const json &j, const std::string &a) {
    try {
      if (exists(j, a)) {
//        std::cout<<"Adding number: "<<a<<" as "<< j[a]<<std::endl;
        if (!j[a].is_null()) {
          return j[a].get<uint64_t>();
        }
      }
    }  catch (int err) {
      std::cout<<"[ERROR] Adding number: "<<a<<" as "<< j[a]<<std::endl;
      return -1;
    }
    return -1;
  }

  std::string net_convert::add_str(const json &j, const std::string &a) {
    try {
      if (exists(j,a)) {
//        std::cout<<"Adding: "<<a<<" as "<< j[a]<<std::endl;
        if(!j[a].is_null()){
          return j[a].get<std::string>();
        }
      }
    } catch (int err) {
      std::cout<<"[ERROR] Adding str: "<<a<<" as "<< j[a]<<std::endl;
      return "";
    }
    return "";
  }
  std::string net_convert::add_bool (const json& j, const std::string & a){
    try {
      if (exists(j,a)) {
//        std::cout<<"Adding: "<<a<<" as "<< j[a]<<std::endl;
        if(!j[a].is_null()){
          return j[a].get<bool>()?"success":"none";
        }
      }
    } catch (int err) {
      std::cout<<"[ERROR] Adding bool: "<<a<<" as "<< j[a]<<std::endl;
      return "";
    }
    return "none";
  }

  int net_convert::get_int(const json &j, const std::string &a) {
    try {
      if (exists(j, a)) {
        if(!j[a].is_null()) {
          return atoi(j[a].get<std::string>().c_str());
        }
      }
    } catch (int err) {
      std::cout << "[ERROR] Adding int: " << a << " as " << j[a] << std::endl;
      return -1;
    }
    return -1;
  }

  std::string net_convert::get_str(const json &j, const std::string &a) {
    try {
      if (exists(j, a)) {
        if(!j[a].is_null()) {
          return j[a].get<std::string>();
        }
      }
    } catch (int err) {
      std::cout << "[ERROR] Adding str: " << a << " as " << j[a] << std::endl;
      return "";
    }
    return "";
  }

}