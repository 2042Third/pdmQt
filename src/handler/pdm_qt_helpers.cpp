//
// Created by Yi Yang on 3/18/2023.
//

#include <QDateTime>
#include "pdm_qt_helpers.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

uint64_t PDM::pdm_qt_helpers::cstrToUint64(const char* str) {
  char* endptr;
  uint64_t value = std::strtoull(str, &endptr, 10);
  if (*endptr != '\0') {
    // Handle conversion error, e.g., invalid characters in the input string
    std::cerr << "Invalid characters in the input string." << std::endl;
  }
  return value;
}
QString PDM::pdm_qt_helpers::unix_time_to_qstr(uint64_t a) {
  QString datetime_string = QDateTime::fromMSecsSinceEpoch(a).toString("yyyy-MM-dd hh:mm:ss"); // Convert QDateTime to string
  return datetime_string;
}
