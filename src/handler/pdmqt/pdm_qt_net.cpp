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


  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) PDM::network::post_callback_heads(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      if (rt->wt.userinfo.status == "success") {
        emit rt->log(std::string(wt->js.dump(4)).c_str(), "#0F0F0F");
        emit rt->noteHeadsSuccess();
      } // End Success block
      else { // Begin Fail block

        emit rt->log("Unsuccessful notes callback. ", "#6C2501");
        emit rt->noteHeadsFail();
      } // End Fail block
      return callback_out;
    }
  };

  std::string j_str;
  auto *rt = (PdmRunTime *) rtt;
  std::cout<< "client_action_note_heads"<<std::endl;
  std::cout<< "userinfo.email: "<<rt->wt.userinfo.email<<std::endl;
  std::cout<< "userinfo.sess: "<<rt->wt.userinfo.sess<<std::endl;
  std::map<std::string,std::string> data=
      PDM::pdm_net_type::get_note_heads(rt->wt.userinfo.sess,rt->wt.userinfo.email,rt->notes.GetHeadsType);
  j_str = PDM::network::get_json(data);

  rt->note_heads_action(j_str, &rt->wt, NetCallBack_::_callback);
  return 0;
}
