//
// Created by Yi Yang on 3/22/2023.
//

#include <sstream>
#include "pdm_settings.h"

PDM::Settings::Settings() {

}

int PDM::Settings::run(const std::string &cmd) {
  if (commandMap.count(cmd)) {
    commandMap[cmd]->execute();
    return 1;
  } else {
    // Handle unknown command
    return 0;
  }
}

int PDM::Settings::run(std::vector<std::string> commands) {
  for (const std::string& segment : commands) {
    if(! run(segment)) {
      break;
    }
  }
  return 1;
}



