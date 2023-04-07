//
// Created by Yi Yang on 3/22/2023.
//

#ifndef PDM_QT_PDM_SETTINGS_H
#define PDM_QT_PDM_SETTINGS_H
namespace PDM{
class Settings {
public:
  int showUsernameInStatusBar = 1;
  // Display Settings
  int display_main_window_x = 0;
  int display_main_window_y = 0;
  int display_main_window_w = 0;
  int display_main_window_h = 0;


  // Debug Status
  int has_database_location = 0;
};
}
#endif //PDM_QT_PDM_SETTINGS_H
