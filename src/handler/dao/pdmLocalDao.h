//
// Created by Yi Yang on 4/1/2023.
//

#ifndef PDM_QT_PDMLOCALDAO_H
#define PDM_QT_PDMLOCALDAO_H


#include <iostream>
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "handler/db/PdmDBType.h"

namespace PDM{
// Local class representing a single row in the pdm_local table
class Local {
public:
  PdmDBType<int> id = PdmDBType<int>("id", "INTEGER", "PRIMARY KEY AUTOINCREMENT");
  PdmDBType<std::string> last_time_open = PdmDBType<std::string>( "last_time_open", "DATETIME", "DEFAULT CURRENT_TIMESTAMP");
  PdmDBType<std::string> data = PdmDBType<std::string>( "data", "TEXT", "");
  Local(int id_, const std::string& last_time_open_, const std::string& data_)
  {
    id.val = id_;
    last_time_open.val = last_time_open_;
    data.val = data_;
  }
  Local()= default;
};

// LocalDao class to handle database operations for the pdm_local table
class LocalDao {
public:
  LocalDao() ;
  ~LocalDao() ;

  void create_table() ;

  int insert(const std::string& data) ;

  std::unique_ptr<Local> find_by_id(int id) ;

  void set_db(sqlite3* db) { db_ = db; }

  // Implement other CRUD methods as needed
  Local db_structure;
private:
  sqlite3* db_ = nullptr;
};
} // Namespace PDM


#endif //PDM_QT_PDMLOCALDAO_H
