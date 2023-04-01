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

// PdmLocal class representing a single row in the pdm_local table
class PdmLocal {
public:
  int id;
  std::string last_time_open;
  std::string data;

  PdmLocal(int id, const std::string& last_time_open, const std::string& data)
      : id(id), last_time_open(last_time_open), data(data) {}
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
