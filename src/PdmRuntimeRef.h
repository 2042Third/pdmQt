//
// Created by Yi Yang on 2/20/2023.
//

#ifndef PDM_QT_PDMRUNTIMEREF_H
#define PDM_QT_PDMRUNTIMEREF_H
#include "PdmRunTime.h"
class PdmRuntimeRef {
public:
  virtual void setRef(PdmRunTime* rtRef){rt = rtRef;}

protected:
  PdmRunTime * rt=nullptr;
};


#endif //PDM_QT_PDMRUNTIMEREF_H
