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
  PdmDBType<int> id_dv = PdmDBType<int>( "id", "INTEGER", "PRIMARY KEY AUTOINCREMENT");
  PdmDBType<std::string> last_time_open_dv = PdmDBType<std::string>( "last_time_open", "DATETIME", "DEFAULT CURRENT_TIMESTAMP");
  PdmDBType<std::string> data_dv = PdmDBType<std::string>( "data", "TEXT", "");

  PdmLocal(int id, const std::string& last_time_open, const std::string& data)
      {
        id_dv.val = id;
        last_time_open_dv.val = last_time_open;
        data_dv.val = data;
      }
};

// PdmLocalDao class to handle database operations for the pdm_local table
class PdmLocalDao {
public:
  PdmLocalDao(const std::string& db_name) ;

  ~PdmLocalDao() ;

  void create_table() ;

  int insert(const std::string& data) ;

  std::unique_ptr<PdmLocal> find_by_id(int id) ;

  // Implement other CRUD methods as needed

private:
  sqlite3* db_;
};


#endif //PDM_QT_PDMLOCALDAO_H
