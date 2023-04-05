//
// Created by Yi Yang on 4/1/2023.
//

#ifndef PDM_QT_PDMDBTYPE_H
#define PDM_QT_PDMDBTYPE_H

#include <string>

template <typename T>
class PdmDBType {
public:
  PdmDBType(T& val, const std::string name, const std::string type, const std::string mod)
      : val(val), name(name), type(type), mod(mod) {}
  PdmDBType( const std::string name, const std::string type, const std::string mod)
      : val(val), name(name), type(type), mod(mod) {}
  T& val;
  const std::string name;
  const std::string type;
  const std::string mod;
  std::string signature(){return name + " " + type + " " + mod;}
};


#endif //PDM_QT_PDMDBTYPE_H
