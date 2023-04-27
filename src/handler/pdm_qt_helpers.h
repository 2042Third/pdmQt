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
    static QString unix_time_to_qstr(uint64_t a);
    static uint64_t cstrToUint64(const char* str);
    static QDateTime unix_time_to_qtime(uint64_t a);
  };
}

#endif //PDM_QT_PDM_QT_HELPERS_H
