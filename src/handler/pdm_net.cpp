//
// Created by Yi Yang on 12/13/2022.
//

#include "pdm_net.h"
#include "net_convert.h"
#include "empp.h"
#include "PdmRunTime.h"
#include <iostream>

namespace PDM{
    const network::_actions network::actions = {
        "https://pdm.pw",
        "https://pdm.pw/auth/signin",
        "https://pdm.pw/auth/signup",
        "https://pdm.pw/auth/note"
    };

    const network::_notes network::notes = {
        "heads",
        "retrieve",
        "new",
        "update",
        "delete"
    };

}

namespace PDM {
  using json = nlohmann::json;



  size_t network::post_callback_signin( char *data, size_t size, size_t nmemb, void *userp){
    auto *wt = (struct NetObj *)userp;
    wt->readptr = std::move(std::string(data,nmemb));
    wt->js = json::parse(wt->readptr);
    PDM::network::get_userinfo(wt->js,wt->userinfo);
    std::cout<< "Signin Return: "<< wt->js<<std::endl;
    return nmemb; /* we copied this many bytes */
  }
  size_t network::post_callback_heads( char *data, size_t size, size_t nmemb, void *userp){
    auto *wt = (struct NetObj *)userp;
    wt->readptr = std::move(std::string(data,nmemb));
    wt->js = json::parse(wt->readptr);
    std::cout<< "Notes Return: "<< wt->js<<std::endl;
    ((PDM::pdmNotesCache*)wt->db)->execute_note_heads(wt->js, wt->userinfo, wt->data);
    return nmemb; /* we copied this many bytes */
  }
  size_t network::post_callback_note( char *data, size_t size, size_t nmemb, void *userp){
    auto *wt = (struct NetObj *)userp;
    wt->readptr = std::move(std::string(data,nmemb));
    wt->js = json::parse(wt->readptr);
    std::cout<< "Note retrieve Return: "<< wt->js<<std::endl;
    std::cout<< "Note retrieve try noteid: "<<net_convert::get_int(wt->js,"note_id")<<std::endl;
    ((PDM::pdmNotesCache*)wt->db)->updateNoteDec(wt->data
                                              ,net_convert::get_int(wt->js,"note_id")
                                              ,net_convert::add_str(wt->js,"content")
                                              );
    return nmemb; /* we copied this many bytes */
  }

  int network::signin_post        (const std::string&a, NetWriter* wt_in,
                                   size_t _callback(char *, size_t , size_t , void *)) {
    post(a,actions.signinURL,  wt_in,_callback);
    return 1;
  }

  void network::post (const std::string& a, const std::string& b, NetWriter* wt,
                      size_t callback(char *,size_t,size_t,void *)) {
    pdm_network::post(a,b, callback, wt);
  }


  network::network() {
  }

  network::~network() {

  }

  void network::get_userinfo(const json &j,UserInfo& userinfo) {
    PDM::net_convert::convert(j,userinfo);
  }

  size_t network::post_callback_update(char *data, size_t size, size_t nmemb, void *userp) {
    auto *wt = (struct NetObj *)userp;
//    wt->readptr = std::move(std::string(data,nmemb));
    wt->js = json::parse(wt->readptr);
    std::cout<< "Note update Return: "<< wt->js<<std::endl;
    std::cout<< "Note update try noteid: "<<net_convert::get_int(wt->js,"note_id")<<std::endl;
    std::cout<< "Note update status: "<< net_convert::get_str(wt->js,"status") <<std::endl;
    std::cout<< "Note update status info: "<< net_convert::get_str(wt->js,"statusInfo") <<std::endl;
//    ((PDM::pdmNotesCache*)wt->db)->updateNote(net_convert::get_int(wt->js,"note_id"),net_convert::add_str(wt->js,"content") );
    return nmemb; /* we copied this many bytes */
  }


} // PDM
