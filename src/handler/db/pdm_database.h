//
// Created by Mike Yang on 11/25/2022.
//

#ifndef PDM_PLATFORMS_UI_PDM_DATABASE_H
#define PDM_PLATFORMS_UI_PDM_DATABASE_H

#include "src/handler/pdm_status.h"
#include "sqlite3.h"
#include "cryptosqlite/cryptosqlite.h"
#include "nlohmann/json.hpp"
#include "src/handler/types.h"

namespace PDM {
class pdm_database : public Status{
public:

  struct return_table{
    int argc=0;
    std::vector<std::vector<std::string>> argv;
    std::vector<std::string> col_name;
  };
  pdm_database();
  ~pdm_database();

  int open_db(const char* name, const char*pas,int pas_size);
  int close_db(char* name);
  int execute(const char *input);

  static void reset (return_table* a) {
    a->argc=0;
    a->argv.clear();
    a->col_name.clear();
  }

  sqlite3 *db{};
  cryptosqlite enc_db;
  char *zErrMsg ;
  int rc;
  return_table current_display_table;
  std::string last_command ;
  int status_open = 0;

  const char *local_table_create_query = "CREATE TABLE IF NOT EXISTS pdm_local("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "last_time_open DATETIME DEFAULT CURRENT_TIMESTAMP,"
    "data TEXT );";

};

}


#endif //PDM_PLATFORMS_UI_PDM_DATABASE_H
