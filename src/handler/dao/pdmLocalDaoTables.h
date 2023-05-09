//
// Created by 18604 on 4/4/2023.
//

#ifndef PDM_QT_PDMLOCALDAOTABLES_H
#define PDM_QT_PDMLOCALDAOTABLES_H
#include "handler/db/PdmDBType.h"
#include <string>
#include <sstream>

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
    int id_val;
    std::string last_time_open_val;
    std::string key_val;
    std::string val_val;
    std::string data_val;

    PdmDBType<int> id = PdmDBType<int>(id_val, "id", "INTEGER", "PRIMARY KEY AUTOINCREMENT");
    PdmDBType <std::string> last_time_open = PdmDBType<std::string>(last_time_open_val, "last_time_open", "DATETIME","DEFAULT CURRENT_TIMESTAMP");
    PdmDBType <std::string> key = PdmDBType<std::string>(key_val, "key", "TEXT", "not null UNIQUE");
    PdmDBType <std::string> val = PdmDBType<std::string>(val_val, "val", "TEXT", "default \'\'");
    PdmDBType <std::string> data = PdmDBType<std::string>(data_val, "data", "TEXT", "default \'\'");

    Local(int idIn, const std::string& last_time_openIn, const std::string& keyIn, const std::string& valIn,
          const std::string& dataIn)
        : id_val(idIn), last_time_open_val(last_time_openIn), key_val(keyIn), val_val(valIn), data_val(dataIn), Table() {
      creation_condition = "IF NOT EXISTS";
      table_name = "pdm_local";
      constraint = "";
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
              + key.signature() + ","
              + val.signature() + ","
             + data.signature()
             + ")"
             + constraint+";";
    }

    /**
     * Get the insert or replace string that requires prepared statements.
     * @return the string
     * */
    std::string insert_replace_str(){
      std::stringstream ss;
      ss << "INSERT OR REPLACE INTO " << table_name << " (key, val, data) VALUES (?,?,?);";
      return ss.str();
    }


  };
  // Stores the last display position of the windows
  class LocalDisplay: Table{
  public:
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
      constexpr auto base_query = "CREATE TABLE ";
      constexpr auto delimiter = ",";
      constexpr auto query_end = ");";

      std::string query;
      query.reserve(512);  // Adjust this value according to the expected query size.

      query.append(base_query);
      query.append(creation_condition);
      query.append(" ");
      query.append(table_name);
      query.append("(");
      query.append(id.signature());
      query.append(delimiter);
      query.append(ref_id.signature());
      query.append(delimiter);
      query.append(last_display_pos_x.signature());
      query.append(delimiter);
      query.append(last_display_pos_y.signature());
      query.append(delimiter);
      query.append(last_display_width.signature());
      query.append(delimiter);
      query.append(last_display_height.signature());
      query.append(delimiter);
      query.append(last_display_maximized.signature());
      query.append(delimiter);
      query.append(last_display_fullscreen.signature());
      query.append(delimiter);
      query.append(window_name.signature());
      query.append(delimiter);
      query.append(constraint);
      query.append(query_end);

      return query;
    }
  };

} // Namespace PDM


#endif //PDM_QT_PDMLOCALDAOTABLES_H
