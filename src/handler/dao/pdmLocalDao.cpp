//
// Created by Yi Yang on 4/1/2023.
//

#include "pdmLocalDao.h"

PdmLocalDao::PdmLocalDao(const std::string& db_name) {
  sqlite3_open(db_name.c_str(), &db_);
  create_table();
}

PdmLocalDao::~PdmLocalDao() {
  sqlite3_close(db_);
}

void PdmLocalDao::create_table() {
  const char* local_table_create_query =
      "CREATE TABLE IF NOT EXISTS pdm_local("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "last_time_open DATETIME DEFAULT CURRENT_TIMESTAMP,"
      "data TEXT );";
  sqlite3_exec(db_, local_table_create_query, nullptr, nullptr, nullptr);
}


int PdmLocalDao::insert(const std::string& data) {
  std::string query = "INSERT INTO pdm_local (data) VALUES (?);";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_TRANSIENT);

  int result = sqlite3_step(stmt) == SQLITE_DONE ? sqlite3_last_insert_rowid(db_) : -1;

  sqlite3_finalize(stmt);
  return result;
}

std::unique_ptr<PdmLocal> PdmLocalDao::find_by_id(int id) {
  std::string query = "SELECT id, last_time_open, data FROM pdm_local WHERE id = ?;";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_int(stmt, 1, id);

  std::unique_ptr<PdmLocal> pdm_local;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    pdm_local = std::make_unique<PdmLocal>(sqlite3_column_int(stmt, 0),
                                           reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                                           reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
  }

  sqlite3_finalize(stmt);
  return pdm_local;
}