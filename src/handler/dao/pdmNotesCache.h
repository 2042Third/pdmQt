//
// Created by Yi Yang on 5/6/2023.
//

#ifndef PDM_QT_PDMNOTESCACHE_H
#define PDM_QT_PDMNOTESCACHE_H

#include "src/handler/types.h"
#include "nlohmann/json.hpp"
#include "cryptosqlite/cryptosqlite.h"
#include "sqlite3.h"
#include "src/handler/pdm_status.h"
#include "handler/db/pdm_database.h"

namespace PDM {

  class pdmNotesCache : public pdm_database {
  public:
    pdmNotesCache();


    void create_table();
    void updateNote( int noteid, const std::string& content);
    int insert(const std::string &key, const std::string &val, const std::string &data = "");
    int execute_note_heads(const nlohmann::json&j, const UserInfo&userinfo, const std::string& data);
    // Static queries
    const std::string add_note_head = "insert or replace into notes(noteid, useremail, content, h, intgrh,time, head)"
                                      " values(?,?,?,?,?,?,?);";
    const char* note_table_create_query = "CREATE TABLE IF NOT EXISTS notes (noteid INTEGER PRIMARY KEY, "
                                          "useremail text not null,"
                                          "content TEXT,"
                                          "h text,"
                                          "intgrh text,"
                                          "time INTEGER , "
                                          "head text); ";

  };
}

#endif //PDM_QT_PDMNOTESCACHE_H
