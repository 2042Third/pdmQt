//
// Created by 18604 on 4/1/2023.
//

#ifndef PDM_QT_PDMDBTYPES_H
#define PDM_QT_PDMDBTYPES_H

#include <string>

template <typename T>
class PdmDBTypes {
public:
  PdmDBTypes(T val, const std::string& name, const std::string& type, const std::string& mod)
      : val(val), name(name), type(type), mod(mod) {}
  T val;
  const std::string &name;
  const std::string &type;
  const std::string &mod;
};


#endif //PDM_QT_PDMDBTYPES_H
