//
// Created by Mike Yang on 11/25/2022.
//

#include "pdm_database.h"
#include "crypto/pdmCryptoDB.hpp"
#include "net_convert.h"
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

int PDM::pdm_database::open_db(const char *name, const char*pas, int pas_size) {
  change(PDM::Status::LOADING);
  cryptosqlite::setCryptoFactory([] (std::unique_ptr<IDataCrypt> &crypt) {
    crypt = std::make_unique<pdm_crypto_db>();
  });
  rc = sqlite3_open_encrypted(name, &db, pas, pas_size); // open the encrypted database
//  rc = sqlite3_open_v2(name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_URI, NULL);
  change(PDM::Status::OPEN);
  if( rc ){
    change(PDM::Status::PDM_ERROR);
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 0;
  }
  return 1;
}

int PDM::pdm_database::close_db(char *name) {
  change(PDM::Status::LOADING);
  sqlite3_close(db);
  change(PDM::Status::CLOSED);
  return 1;
}

int PDM::pdm_database::execute(char *input) {
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

int PDM::pdm_database::execute_note_heads(const nlohmann::json&j,const UserInfo&userinfo) {
  sqlite3_stmt* stmt = 0;
  rc = sqlite3_prepare_v2( db, add_note_head.c_str(), -1, &stmt, 0 );

//  Optional, but will most likely increase performance.
  rc = sqlite3_exec( db, "BEGIN TRANSACTION", 0, 0, 0 );

  for ( auto&i: j["content"] ) {
    //  Bind-parameter indexing is 1-based.
    rc = sqlite3_bind_int( stmt, 1, atoi(i["note_id"].get<std::string>().c_str()) );
    rc = sqlite3_bind_text( stmt, 2, userinfo.email.c_str(), -1, SQLITE_TRANSIENT );
    rc = sqlite3_bind_text( stmt, 3, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text( stmt, 4, j["h"].get<std::string>().c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text( stmt, 5, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_int(  stmt, 6, atoi(i["time"].get<std::string>().c_str()) );
    rc = sqlite3_bind_text( stmt, 7, PDM::net_convert::add_str(i,"head").c_str(), -1, SQLITE_TRANSIENT);
    while ( sqlite3_step( stmt ) == SQLITE_ROW ) { // While query has result-rows.
      for ( int colIndex = 0; colIndex < sqlite3_column_count( stmt ); colIndex++ ) {
        int result = sqlite3_column_int( stmt, colIndex );
      }
    }
    //  Step, Clear and Reset the statement after each bind.
    rc = sqlite3_step( stmt );
    rc = sqlite3_clear_bindings( stmt );
    rc = sqlite3_reset( stmt );
  }
  char *zErrMsg = 0;  //  Can perhaps display the error message if rc != SQLITE_OK.
  rc = sqlite3_exec( db, "END TRANSACTION", 0, 0, &zErrMsg );   //  End the transaction.
  if( rc!=SQLITE_OK ){
    change(PDM::Status::PDM_ERROR);
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    return 0;
  }
  rc = sqlite3_finalize( stmt );  //  Clean up the statements

  return 0;
}


