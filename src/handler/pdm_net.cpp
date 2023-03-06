//
// Created by Yi Yang on 12/13/2022.
//

#include "pdm_net.h"
#include "net_convert.h"
#include <iostream>

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
    wt->db->execute_note_heads(wt->js, wt->userinfo);
    return nmemb; /* we copied this many bytes */
  }

  int network::signin_post        (const std::string&a, NetWriter* wt_in,
                                   size_t _callback(char *, size_t , size_t , void *)) {
    post(a,actions.signinURL,  wt_in,_callback);
    return 1;
  }

  int network::note_heads_action  (const std::string &a, NetWriter *wt_in,
                                   size_t _callback(char *, size_t , size_t , void *)) {
    post(a,actions.notesGetHeadsURL,  wt_in,_callback);
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



} // PDM