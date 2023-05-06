//
// Created by Mike Yang on 11/25/2022.
//

#include "pdm_database.h"
#include "crypto/pdmCryptoDB.hpp"
#include "src/handler/net_convert.h"
#include <memory>
#include <string>

namespace PDM {
  static int callback(void *ptr, int argc, char **argv, char **azColName) {
    using tbl_type = PDM::pdm_database::return_table;
    auto* table = static_cast<tbl_type*>(ptr);

    int i;
    std::vector<std::string> tmp;
    if(table->argc==0){ // first time recording
      table->argc = argc;
      for (unsigned f =0 ;f<argc;f++) {
        if (azColName[f]) table->col_name.push_back(std::move(std::string(azColName[f])));
        else table->col_name.push_back(std::move(std::string("")));
      }
    }
    for (i = 0; i < argc; i++) {
      if (argv[i]) tmp.push_back(std::move(std::string(argv[i])));
      else tmp.push_back(std::move(std::string("")));
    }
    table->argv.push_back(std::move(tmp));
    printf("\n");
    return 0;
  }

  pdm_database::pdm_database() {
  }

  pdm_database::~pdm_database() {

  }
}
/**
 * Open a database file.
 * @param name name and path of the database file
 * @param pas password
 * @param pas_size size of the password
 * Checks if the path given is good. If not, make path.
 * */
int PDM::pdm_database::open_db(const char *name, const char*pas, int pas_size) {
  namespace fs = std::filesystem;
  change(PDM::Status::LOADING);
  fs::create_directories(fs::path(name).parent_path()); // Create user config dir
  cryptosqlite::setCryptoFactory([] (std::unique_ptr<IDataCrypt> &crypt) { // set the crypto factory
    crypt = std::make_unique<pdm_crypto_db>();
  });
  rc = sqlite3_open_encrypted(name, &db, pas, pas_size); // open the encrypted database
  change(PDM::Status::OPEN);
  if( rc ){
    status_open = 0;
    change(PDM::Status::PDM_ERROR);
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 0;
  }
  status_open = 1;
  return 1;
}

int PDM::pdm_database::close_db(char *name) {
  change(PDM::Status::LOADING);
  sqlite3_close(db);
  change(PDM::Status::CLOSED);
  status_open=0;
  return 1;
}

int PDM::pdm_database::execute(const char *input) {
  change(PDM::Status::LOADING);
  reset(&current_display_table);
  rc = sqlite3_exec(db, input, callback, &current_display_table, &zErrMsg);
  if( rc!=SQLITE_OK ){
    change(PDM::Status::PDM_ERROR);
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    return 0;
  }
  last_command = input;
  change(PDM::Status::OPEN);
  return 1;
}


