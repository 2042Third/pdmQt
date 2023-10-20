//
// Created by Yi Yang on 4/25/2023.
//

#ifndef PDM_QT_PDM_QT_NET_H
#define PDM_QT_PDM_QT_NET_H


#include <string>
#include "PdmRunTime.h"

namespace PDM {
  class pdm_qt_net {
  public:
    static int client_action_note_heads(void *rtt);
    static int client_action_note_retrieve(void *rtt, int noteId); // retrieve note
    static void client_action_note_create(PdmRunTime *rt);
  };
}

#endif //PDM_QT_PDM_QT_NET_H
