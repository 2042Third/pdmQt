//
// Created by Yi Yang on 4/1/2023.
//

#include <sstream>
#include "pdmLocalDao.h"

PdmLocalDao::PdmLocalDao() {
}
PdmLocalDao::PdmLocalDao(sqlite3* db) {
  db_ = db;
}

PdmLocalDao::~PdmLocalDao() {
}

void PdmLocalDao::create_table() {
  if(db_== nullptr){std::cout << "db is null" << std::endl;return;}
  std::stringstream ss;
  ss << "create table if not exists ";
  ss << "pdm_local"; // database name
  ss << "(";
  ss << db_structure.id.signature()<< ",";
  ss << db_structure.last_time_open.signature()<< ",";
  ss << db_structure.data.signature();
  ss << ");";
  sqlite3_exec(db_, ss.str().c_str(), nullptr, nullptr, nullptr);
}


int PdmLocalDao::insert(const std::string& data) {
  if(db_== nullptr){std::cout << "db is null" << std::endl;return 0;}
  std::string query = "INSERT INTO pdm_local (data) VALUES (?);";
  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_TRANSIENT);

  int result = sqlite3_step(stmt) == SQLITE_DONE ? sqlite3_last_insert_rowid(db_) : -1;

  sqlite3_finalize(stmt);
  return result;
}

std::unique_ptr<PdmLocal> PdmLocalDao::find_by_id(int id) {
  if(db_== nullptr){std::cout << "db is null" << std::endl;return nullptr;}
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