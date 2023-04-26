//
// Created by Yi Yang on 4/25/2023.
//

#include "pdm_qt_net.h"

#include "handler/pdm_net_type.h"
#include "PdmRunTime.h"

/**
 * Pdm QT's get notes heads method.
 * @param rtt: pdm runtime pointer.
 * */
int PDM::pdm_qt_net::client_action_note_heads(void *rtt) {
  std::string j_str;
  auto *rt = (PdmRunTime *) rtt;
  std::cout<< "client_action_note_heads"<<std::endl;
  std::cout<< "userinfo.email: "<<rt->wt.userinfo.email<<std::endl;
  std::cout<< "userinfo.sess: "<<rt->wt.userinfo.sess<<std::endl;
  std::map<std::string,std::string> data=
      PDM::pdm_net_type::get_note_heads(rt->wt.userinfo.sess,rt->wt.userinfo.email,rt->notes.GetHeadsType);
  j_str = PDM::network::get_json(data);

  rt->note_heads_action(j_str, &rt->wt);
  return 0;
}
