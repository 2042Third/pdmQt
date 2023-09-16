//
// Created by Yi Yang on 3/22/2023.
//

#include <sstream>
#include <iostream>
#include "pdm_settings.h"
#include "pdm_qt_helpers.h"

#define SETTING_STRING_EMITTER_BLUE(x) \
  emit log((std::string(#x "=")+std::to_string(x)).c_str(), "#0000FF");

PDM::Settings::Settings() {

}

int PDM::Settings::run(const std::string &cmd) {
  std::vector<std::string> tokens = PDM::pdm_qt_helpers::splitString(cmd, '=');

  if(tokens.size() == 1){
    if (commandMap.count(tokens[0])) {
      commandMap[tokens[0]]->execute();
      return 1;
    }
  }
  else if(tokens.size() ==2) {
    std::cout<<"No action implemented for token size 2!"<<std::endl;
    return 0;
  }
  else if(tokens.size() == 3){
    std::cout<<"No action implemented for token size 3!"<<std::endl;
    return 0;
  }
  return 0;
}

int PDM::Settings::run(std::vector<std::string> commands) {
  for (const std::string& segment : commands) {
    if(! run(segment)) {
      break;
    }
  }
  return 1;
}



