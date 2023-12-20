//
// Created by Yi Yang on 3/18/2023.
//

#include <QDateTime>
#include "pdm_qt_helpers.h"
#include "nlohmann/json.hpp"
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
/**
 * Beautify the json string.
 * @param s the json string to be beautified.
 * @return the beautified json string.
 * */
std::string PDM::pdm_qt_helpers::json_b (const std::string &s) {
  std::string s_out;
  using json = nlohmann::json;
  json j = json::parse(s);
  s_out = j.dump(4);

  // Change newline symbol to <br>
  size_t pos = 0;
  while ((pos = s_out.find("\n", pos)) != std::string::npos) {
    size_t start = pos;
    while (s_out[++pos] == ' ');

    std::string indent((pos - start - 1) * 4, ' '); // 4 spaces for each indentation level
    for (size_t i = 0; i < indent.size(); ++i) {
      if (indent[i] == ' ') {
        indent.erase(i, 1);
        indent.insert(i, "&nbsp;");
      }
    }

    s_out.replace(start, pos - start, "<br>" + indent);
  }

  return s_out;
}

