//
// Created by Yi Yang on 4/1/2023.
//

#include <sstream>
#include "pdmLocalDao.h"

PDM::LocalDao::LocalDao() {

}

PDM::LocalDao::~LocalDao() {
}

void PDM::LocalDao::create_table() {
  if(!status_open){std::cout << "db is null" << std::endl;return;}
  execute(local.get_table_create_string().c_str()); // Create the local table

//  static std::string a = local_display.get_table_create_string();
//  execute(local_display.get_table_create_string().c_str()); // Create the local_display table
}

/**
 * Insert insert or replaces a key value pair into the local table.
 * */
int PDM::LocalDao::insert(const std::string& key, const std::string& val, const std::string& data ) {
  std::string query = "INSERT or replace INTO pdm_local (key, val, data) VALUES (?, ?, ?);";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, val.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, data.c_str(), -1, SQLITE_TRANSIENT);

  int result = sqlite3_step(stmt) == SQLITE_DONE ? sqlite3_last_insert_rowid(db) : -1;

  sqlite3_finalize(stmt);
  return result;
}

std::unique_ptr<PDM::Local> PDM::LocalDao::find_by_id(int id) {
  if(!status_open){std::cout << "db is null" << std::endl;return nullptr;}
  std::string query = "SELECT id, last_time_open, key, val, data FROM pdm_local WHERE id = ?;";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_int(stmt, 1, id);

  std::unique_ptr<Local> pdm_local;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    pdm_local = std::make_unique<Local>(sqlite3_column_int(stmt, 0), // id
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)), // last_time_open
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)), // key
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)), // val
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)) // data
                                        );
  }

  sqlite3_finalize(stmt);
  return pdm_local;
}

std::unique_ptr<PDM::Local> PDM::LocalDao::find_by_key(const std::string &key) {
  if(!status_open){
    std::cout << "db is null" << std::endl;
    return nullptr;
  }

  std::string query = "SELECT id, last_time_open, key, val, data FROM pdm_local WHERE key = ?;";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);

  std::unique_ptr<Local> pdm_local;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    pdm_local = std::make_unique<Local>(
        sqlite3_column_int(stmt, 0), // id
        getStrReturn(stmt,1), // last_time_open
        getStrReturn(stmt,2), // key
        getStrReturn(stmt,3), // val
        getStrReturn(stmt,4) // data
    );
  } else {
    std::cout << "No record found with key: " << key << std::endl;
  }

  sqlite3_finalize(stmt);
  return pdm_local;
}
