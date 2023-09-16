//
// Created by Yi Yang on 3/22/2023.
//

#ifndef PDM_QT_PDM_SETTINGS_H
#define PDM_QT_PDM_SETTINGS_H

#include <memory>
#include <map>
#include "pdm_command.h"
namespace PDM{
class Settings {
public:
  Settings();
  // Run pdm_command
  int run(const std::string &commandName);
  int run(std::vector<std::string> commands);

  int showUsernameInStatusBar = 1;
  // Display Settings
  int display_main_window_x = 0;
  int display_main_window_y = 0;
  int display_main_window_w = 0;
  int display_main_window_h = 0;


  // Debug Status
  int has_database_location = 0;

  std::map<std::string, std::unique_ptr<pdm_command>> commandMap;
};
}
#endif //PDM_QT_PDM_SETTINGS_H
