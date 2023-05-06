//
// Created by Yi Yang on 5/6/2023.
//

#include <string>
#include <memory>
#include "src/handler/net_convert.h"
#include "crypto/pdmCryptoDB.hpp"
#include "pdmNotesCache.h"

void PDM::pdmNotesCache::updateNote(int noteid, const std::string &content) {

}

/**
 * Execute a query and return the result.
 * * need to move this to a different file
 * @param input query
 * @return result of the query
 * */
int PDM::pdmNotesCache::execute_note_heads(const nlohmann::json&j, const UserInfo&userinfo, const string& data) {
  sqlite3_stmt* stmt = 0;
//  std::string headstr;
  rc = sqlite3_prepare_v2( db, add_note_head.c_str(), -1, &stmt, 0 );

//  Optional, but will most likely increase performance.
  rc = sqlite3_exec( db, "BEGIN TRANSACTION", 0, 0, 0 );

  for ( auto&i: j["content"] ) {
    //  Bind-parameter indexing is 1-based.
    rc = sqlite3_bind_int( stmt, 1, atoi(i["note_id"].get<string>().c_str()) );
    rc = sqlite3_bind_text( stmt, 2, userinfo.email.c_str(), -1, SQLITE_TRANSIENT );
    rc = sqlite3_bind_text( stmt, 3, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text(stmt, 4, j["h"].get<string>().c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text( stmt, 5, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_int(  stmt, 6, atoi(i["time"].get<string>().c_str()) );
    string headstr = net_convert::add_str(i,"head");
    rc = sqlite3_bind_text( stmt, 7, headstr.size()?loader_out(data,headstr).c_str():"", -1, SQLITE_TRANSIENT);
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
    change(PDM_ERROR);
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    return 0;
  }
  rc = sqlite3_finalize( stmt );  //  Clean up the statements

  return 0;
}

PDM::pdmNotesCache::pdmNotesCache():pdm_database() {

}


