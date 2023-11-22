//
// Created by Yi Yang on 5/6/2023.
//

#include <string>
#include <memory>
#include "src/handler/net_convert.h"
#include "crypto/pdmCryptoDB.hpp"
#include "pdmNotesCache.h"
#include "handler/pdm_qt_helpers.h"

PDM::pdmNotesCache::pdmNotesCache():pdm_database() {

}

void PDM::pdmNotesCache::updateNote(int noteid, const std::string &content, const std::string &h) {
  std::fprintf(stdout, "Note retrieve updating database: note id=%d\n", noteid);
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE notes SET content = ?, h=? WHERE noteid = ?;";

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (prepare): " << sqlite3_errmsg(db) << std::endl;
    return;
  }

  // Bind content (first parameter)
  rc = sqlite3_bind_text(stmt, 1, content.c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind content): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Bind hash (Second parameter)
  rc = sqlite3_bind_text(stmt, 2, h.c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind content): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }
  // Bind noteid (second parameter)
  rc = sqlite3_bind_int(stmt, 3, noteid);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind noteid): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Execute the statement
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error (step): " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
}
void PDM::pdmNotesCache::updateNoteEnc(const std::string &key,int noteid, const std::string &content) {
  std::fprintf(stdout, "Note retrieve Encrypted updating database: note id=%d\n", noteid);
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE notes SET content = ?, h=? WHERE noteid = ?;";

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (prepare): " << sqlite3_errmsg(db) << std::endl;
    return;
  }

  // Bind content (first parameter)
  std::string content_copy = content;

  std::string processedContent = !content_copy.empty() ? loader_check(key, content_copy) : "";
  rc = sqlite3_bind_text(stmt, 1, processedContent.c_str(), -1, SQLITE_TRANSIENT);
  cc20_utility::gen_byte_rand_cc20((uint8_t*)content_copy.data(),content_copy.size());
//  rc = sqlite3_bind_text(stmt, 1, !content.empty()?loader_check(key,content).c_str():"", -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind content): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }
  // Bind hash (Second parameter)
  rc = sqlite3_bind_text(stmt, 2, !content.empty()?get_hash(content).c_str():get_hash("").c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind content): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Bind noteid (third parameter)
  rc = sqlite3_bind_int(stmt, 3, noteid);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind noteid): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Execute the statement
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error (step): " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
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
  rc = sqlite3_exec( db, "BEGIN TRANSACTIO", 0, 0, 0 );

  for ( auto&i: j["content"] ) {
    //  Bind-parameter indexing is 1-based.
    NoteHead head;
    net_convert::convert(i, head);
    rc = sqlite3_bind_int( stmt, 1, stoi(head.note_id) );
    rc = sqlite3_bind_text( stmt, 2, userinfo.email.c_str(), -1, SQLITE_TRANSIENT );
    rc = sqlite3_bind_text( stmt, 3, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text(stmt, 4, j["h"].get<string>().c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_text( stmt, 5, "\0", -1, SQLITE_TRANSIENT);
    rc = sqlite3_bind_double(  stmt, 6, head.time );
    rc = sqlite3_bind_text( stmt, 7, head.head.c_str(), -1, SQLITE_TRANSIENT);
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
    change(ERROR_STATE);
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    return 0;
  }
  rc = sqlite3_finalize( stmt );  //  Clean up the statements

  return 0;
}

int PDM::pdmNotesCache::getNote(int noteid, const std::string& data, NoteMsg* note) {
  // Add note heads to the note list.
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT head, h, time, content FROM notes WHERE noteid = ?"; // Adjust the SQL to fit your schema
  int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cout<< "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    return 0;
  }

  // Bind the user's email to the query
  rc = sqlite3_bind_int(stmt, 1, noteid);
  if (rc != SQLITE_OK) {
    std::cout<< "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    return 0;
  }
  // Execute the query and display the note to the tab
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string headstr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    std::string title = (headstr.size()?loader_out(data,headstr).c_str():"");
    std::string h =  (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    size_t date = sqlite3_column_int(stmt, 2);
    std::string content = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    note->head=title;
    note->note_id=noteid;
    note->time = date;
    note->h = h;
    note->content = content.size()?loader_out(data,content).c_str():"";
  }
  // Clean up
  sqlite3_finalize(stmt);
  return 0;
}

int PDM::pdmNotesCache::addAllToNoteList(const string &data, const std::string& email, NotesScroll *noteList) {
  // Add note heads to the note list.
  sqlite3_stmt* stmt = nullptr;
  const char* query = "SELECT head, h, time, noteid FROM notes WHERE useremail = ?"; // Adjust the SQL to fit your schema
  int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cout<< "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    return 0;
  }

  // Bind the user's email to the query
  rc = sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cout<< "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    return 0;
  }
  // Execute the query and add each result to the model
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    NoteHead head;
    std::string headstr = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    head.head = headstr.size()?loader_out(data,headstr):"";
    head.time = sqlite3_column_double(stmt, 2);
    uint64_t tmp = uint64_t(head.time);
    head.ctime = PDM::pdm_qt_helpers::unix_time_to_qstr_sec(tmp).toStdString();
    head.note_id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

    noteList->addNote(head);
  }
  // Clean up
  sqlite3_finalize(stmt);
  return 1;
}

void PDM::pdmNotesCache::updateNoteHead(const string &key, int noteid, const string &head) {
  std::fprintf(stdout, "Note retrieve updating database: note id=%d\n", noteid);
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE notes SET h = ? WHERE noteid = ?;";

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (prepare): " << sqlite3_errmsg(db) << std::endl;
    return;
  }

  // Bind content (first parameter)
  rc = sqlite3_bind_text(stmt, 1, head.size()?loader_check(key,head).c_str():"", -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind content): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Bind plaintext hash (second parameter)
  rc = sqlite3_bind_int(stmt, 2, noteid);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error (bind noteid): " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  // Execute the statement
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "SQL error (step): " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);

}


