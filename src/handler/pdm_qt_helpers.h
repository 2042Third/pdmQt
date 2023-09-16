//
// Created by Yi Yang on 3/18/2023.
//

#ifndef PDM_QT_PDM_QT_HELPERS_H
#define PDM_QT_PDM_QT_HELPERS_H
#include <QString>
#include <QDateTime>

namespace PDM {
  class  pdm_qt_helpers {
  public:
    static QString unix_time_to_qstr(int64_t a);
    static uint64_t cstrToUint64(const char* str);
    static double cstrToDouble(const char* str);
    static double strToDouble(const std::string& str);
    static QDateTime unix_time_to_qtime(uint64_t a);
    static QString unix_time_to_qstr_sec(int64_t a);

    static std::vector<std::string> splitString(const std::string& s, char delimiter);
  };
}

#endif //PDM_QT_PDM_QT_HELPERS_H
