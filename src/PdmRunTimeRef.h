//
// Created by Yi Yang on 2/20/2023.
//

#ifndef PDM_QT_PDMRUNTIMEREF_H
#define PDM_QT_PDMRUNTIMEREF_H
#include "PdmRunTime.h"
class PdmRunTimeRef {
public:
  explicit PdmRunTimeRef(PdmRunTime * rtIn = nullptr) {
    rt = rtIn;
  }

protected:
  PdmRunTime * rt=nullptr;
};


#endif //PDM_QT_PDMRUNTIMEREF_H
