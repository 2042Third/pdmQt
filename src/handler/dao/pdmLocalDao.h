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
  class LocalDao: public pdm_database{
  public:
    LocalDao() ;
    ~LocalDao() ;

    void create_table() ;
    int insert(const std::string& key, const std::string& val, int replace = 0, const std::string& data="");
    int del(const std::string& key);
    std::unique_ptr<Local> find_by_id(int id) ;
    std::unique_ptr<Local> find_by_key(const std::string& key) ;
    Local local; // Local table object, contain the id of the settings

  };
} // Namespace PDM


#endif //PDM_QT_PDMLOCALDAO_H
