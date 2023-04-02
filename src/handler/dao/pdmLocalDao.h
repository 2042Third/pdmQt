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

// PdmLocal class representing a single row in the pdm_local table
class PdmLocal {
public:
  PdmDBType<int> id = PdmDBType<int>("id", "INTEGER", "PRIMARY KEY AUTOINCREMENT");
  PdmDBType<std::string> last_time_open = PdmDBType<std::string>( "last_time_open", "DATETIME", "DEFAULT CURRENT_TIMESTAMP");
  PdmDBType<std::string> data = PdmDBType<std::string>( "data", "TEXT", "");

  PdmLocal(int id_, const std::string& last_time_open_, const std::string& data_)
      {
        id.val = id_;
        last_time_open.val = last_time_open_;
        data.val = data_;
      }
      PdmLocal();
};

// PdmLocalDao class to handle database operations for the pdm_local table
class PdmLocalDao {
public:
  PdmLocalDao() ;
  PdmLocalDao(sqlite3* db) ;

  ~PdmLocalDao() ;

  void create_table() ;

  int insert(const std::string& data) ;

  std::unique_ptr<PdmLocal> find_by_id(int id) ;

  void set_db(sqlite3* db) { db_ = db; }

  // Implement other CRUD methods as needed
  PdmLocal db_structure;
private:
  sqlite3* db_ = nullptr;
};


#endif //PDM_QT_PDMLOCALDAO_H
