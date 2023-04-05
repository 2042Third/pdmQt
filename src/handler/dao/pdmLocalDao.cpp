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
  execute(local_display.get_table_create_string().c_str()); // Create the local_display table
}


int PDM::LocalDao::insert(const std::string& data) {
  if(!status_open){std::cout << "db is null" << std::endl;return 0;}
  std::string query = "INSERT INTO pdm_local (data) VALUES (?);";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_TRANSIENT);

  int result = sqlite3_step(stmt) == SQLITE_DONE ? sqlite3_last_insert_rowid(db) : -1;

  sqlite3_finalize(stmt);
  return result;
}

std::unique_ptr<PDM::Local> PDM::LocalDao::find_by_id(int id) {
  if(!status_open){std::cout << "db is null" << std::endl;return nullptr;}
  std::string query = "SELECT id, last_time_open, data FROM pdm_local WHERE id = ?;";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_int(stmt, 1, id);

  std::unique_ptr<Local> pdm_local;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    pdm_local = std::make_unique<Local>(sqlite3_column_int(stmt, 0),
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                                        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
  }

  sqlite3_finalize(stmt);
  return pdm_local;
}