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
#include "handler/db/pdm_database.h"
#include "pdmLocalDaoTables.h"

namespace PDM{
// LocalDao class to handle database operations for the pdm_local table
class LocalDao: pdm_database{
public:
  LocalDao() ;
  ~LocalDao() ;

  void create_table() ;

  int insert(const std::string& data) ;

  std::unique_ptr<Local> find_by_id(int id) ;

  // Implement other CRUD methods as needed
  Local local;
private:
};
} // Namespace PDM


#endif //PDM_QT_PDMLOCALDAO_H
