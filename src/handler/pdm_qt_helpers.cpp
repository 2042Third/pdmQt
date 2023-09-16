//
// Created by Yi Yang on 3/18/2023.
//

#include <QDateTime>
#include "pdm_qt_helpers.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>

uint64_t PDM::pdm_qt_helpers::cstrToUint64(const char* str) {
  char* endptr;
  uint64_t value = std::strtoull(str, &endptr, 10);
  if (*endptr != '\0') {
    // Handle conversion error, e.g., invalid characters in the input string
    std::cerr << "Invalid characters in the input string." << std::endl;
  }
  return value;
}
double PDM::pdm_qt_helpers::cstrToDouble(const char* str) {
  char* endptr;
  double value = std::strtoull(str, &endptr, 10);
  if (*endptr != '\0') {
    // Handle conversion error, e.g., invalid characters in the input string
    std::cerr << "Invalid characters in the input string." << std::endl;
  }
  return value;
}
double PDM::pdm_qt_helpers::strToDouble(const std::string& str) {
  if(str.size() <= 0) return -1;
  return std::stod(str);
}

QString PDM::pdm_qt_helpers::unix_time_to_qstr(int64_t a) {
  QString datetime_string = QDateTime::fromMSecsSinceEpoch(a).toString("yyyy-MM-dd hh:mm:ss"); // Convert QDateTime to string
  return datetime_string;
}
QString PDM::pdm_qt_helpers::unix_time_to_qstr_sec(int64_t a) {
  QString datetime_string = QDateTime::fromSecsSinceEpoch(a).toString("yyyy-MM-dd hh:mm:ss"); // Convert QDateTime to string
  return datetime_string;
}
QDateTime PDM::pdm_qt_helpers::unix_time_to_qtime(uint64_t a) {
  return QDateTime::fromMSecsSinceEpoch(a);
}

std::vector<std::string> PDM::pdm_qt_helpers::splitString(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);

  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;

}

