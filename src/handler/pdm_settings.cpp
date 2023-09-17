//
// Created by Yi Yang on 3/22/2023.
//

#include <sstream>
#include <iostream>
#include "pdm_settings.h"
#include "pdm_qt_helpers.h"

#define PdmRunTime_SETTING_STRING_EMITTER_BLUE(x) \
  emit log((std::string(#x "=")+std::to_string(x)).c_str(), "#0000FF");

PDM::Settings::Settings() {

}
/**
 * @return 0 if command not found
 * @return -1 if command found but no value
 * @return 1 if command found and value set, and calls execute()
 * */
int PDM::Settings::run(const std::string &cmd) {
  std::vector<std::string> tokens = PDM::pdm_qt_helpers::splitString(cmd, '=');

  if(tokens.size() == 1){
    if (commandMap.count(tokens[0])) {
      return -1;
    }
    return 0;
  }
  else if(tokens.size() ==2) {
    if (commandMap.count(tokens[0])) {
      commandMap[tokens[0]]->setValue(PDM::pdm_qt_helpers::strToDouble(tokens[1]));
      commandMap[tokens[0]]->execute();
      return 1;
    }
    return 0;
  }
  return 0;
}





