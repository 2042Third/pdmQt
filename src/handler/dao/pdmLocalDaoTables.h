//
// Created by 18604 on 4/4/2023.
//

#ifndef PDM_QT_PDMLOCALDAOTABLES_H
#define PDM_QT_PDMLOCALDAOTABLES_H
#include "handler/db/PdmDBType.h"
#include <string>

namespace PDM {
  // Base class for all tables
  class Table{
  public:
    std::string creation_condition ;
    std::string constraint; // constraint
    std::string table_name; // table name
    virtual std::string get_table_create_string() = 0;
  };


// Local class representing a single row in the pdm_local table
  class Local : Table{ // basic data and sets the id
  public:
    PdmDBType<int> id = PdmDBType<int>("id", "INTEGER", "PRIMARY KEY AUTOINCREMENT");
    PdmDBType <std::string> last_time_open = PdmDBType<std::string>("last_time_open", "DATETIME",
                                                                    "DEFAULT CURRENT_TIMESTAMP");
    PdmDBType <std::string> data = PdmDBType<std::string>("data", "TEXT", "");

    Local(int id_, const std::string &last_time_open_, const std::string &data_):Local() {
      id.val = id_;
      last_time_open.val = last_time_open_;
      data.val = data_;
    }

    Local() {
      creation_condition = "IF NOT EXISTS";
      table_name = "pdm_local";
      constraint = "";
    }

    std::string get_table_create_string() override  {
      return "CREATE TABLE " + creation_condition + " " + table_name + "("
             + id.signature() + ","
             + last_time_open.signature() + ","
             + data.signature()
             + ")"
             + constraint+";";
    }

  };
  // Stores the last display position of the windows
  class LocalDisplay: Table{
    PdmDBType<int> id = PdmDBType<int>("id", "INTEGER", " NOT NULL PRIMARY KEY AUTOINCREMENT");
    PdmDBType<int> ref_id = PdmDBType<int>("ref_id", "INTEGER", " NOT NULL");
    PdmDBType<int> last_display_pos_x = PdmDBType<int>("posx", "INTEGER", "");
    PdmDBType<int> last_display_pos_y = PdmDBType<int>("posy", "INTEGER", "");
    PdmDBType<int> last_display_width = PdmDBType<int>("width", "INTEGER", "");
    PdmDBType<int> last_display_height = PdmDBType<int>("height", "INTEGER", "");
    PdmDBType<int> last_display_maximized = PdmDBType<int>("maximized", "INTEGER", "");
    PdmDBType<int> last_display_fullscreen = PdmDBType<int>("fullscreen", "INTEGER", "");
    PdmDBType<std::string> window_name = PdmDBType<std::string>("window_name", "TEXT", "");

    LocalDisplay(){
      creation_condition = "IF NOT EXISTS";
      table_name = "local_display";
      constraint = "FOREIGN KEY(ref_id) REFERENCES "+table_name+"(id) ON DELETE CASCADE";
    }

    std::string get_table_create_string() override {
      return "CREATE TABLE " + creation_condition + " " + table_name + "("
             + id.signature() + ","
             + ref_id.signature() + ","
             + last_display_pos_x.signature() + ","
             + last_display_pos_y.signature() + ","
             + last_display_width.signature() + ","
             + last_display_height.signature() + ","
             + last_display_maximized.signature() + ","
             + last_display_fullscreen.signature() + ","
             + window_name.signature()
             + constraint
             + ")"
             +";";
    }
  };

} // Namespace PDM


#endif //PDM_QT_PDMLOCALDAOTABLES_H
