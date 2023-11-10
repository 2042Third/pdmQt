//
// Created by Yi Yang on 12/21/2022.
//

#ifndef PDM_PLATFORMS_UI_TYPES_H
#define PDM_PLATFORMS_UI_TYPES_H

#include <string>

namespace PDM {
  struct UserInfo {
    std::string msg;
    std::string username;
    std::string msgh;
    std::string email;
    std::string val;
    std::string typestring;
    std::string h ;
    std::string senderstring;
    std::string sess ;
    std::string status ;
    std::string statusInfo ;
    std::string receiverstring;
    std::string authdata;
    double time=-1;
    double update_time=-1;
    std::string utime;
    std::string pdmSecurityVersion;
    std::string checker;
    std::string ctime;
    std::string netStatus ;
  };

  struct NoteHead {
    std::string head ;
    std::string note_id;
    uint64_t uid = -1;
    double time=-1;
    double update_time=-1;
    std::string utime ;
    std::string ctime ;
    uint64_t key=-1;
    // Define the equality operator
    friend bool operator==(const NoteHead &lhs, const NoteHead &rhs) {
      return lhs.note_id == rhs.note_id; // Compare based on the note_id or any other suitable member
    }
  };

  struct NoteMsg : NoteHead {
    std::string content;
    std::string email;
    std::string session;
    std::string ntype;
    std::string sess;
    std::string h;
    std::string username;
    std::string status;
    std::string statusInfo;
    std::string encry;
    std::string hash;
  };
  struct NoteHeads {
    std::vector<NoteHead> v;
  };
}
#endif //PDM_PLATFORMS_UI_TYPES_H
