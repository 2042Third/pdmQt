//
// Created by Yi Yang on 4/25/2023.
//

#include "pdm_qt_net.h"

#include "handler/pdm_net_type.h"
#include "PdmRunTime.h"
#include "empp.h"
#include <QtConcurrent/QtConcurrent>

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
  std::map<std::string,std::string>
      data= PDM::pdm_net_type::getNoteHeadsJsonStr(rt->wt.userinfo.sess, rt->wt.userinfo.email, rt->notes.GetHeadsType);
  j_str = PDM::network::get_json(data);

  QtConcurrent::run(PdmRunTime::post,j_str,rt->actions.notesGetHeadsURL,&rt->wt,NetCallBack_::_callback);
  return 0;
}


/**
 * Pdm QT's get notes retrieve method.
 * @param rtt: pdm runtime pointer.
 * */
int PDM::pdm_qt_net::client_action_note_retrieve(void *rtt, int noteId) {
  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) PDM::network::post_callback_note(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      std::cout << "Note retrieve callback finished and calling noteRetrieveSuccess. " << std::endl;
      if (rt->wt.userinfo.status == "success") {
        int noteId = net_convert::get_int(wt->js,"note_id");
        std::cout << "Note retrieve success: "<<noteId << std::endl;
        emit rt->noteRetrieveSuccess(noteId );
      } // End Success block
      else { // Begin Fail block
        std::cout << "Note retrieve failure: " << std::endl;
        emit rt->log("Unsuccessful notes callback. ", "#6C2501");
        emit rt->noteRetrieveFail(net_convert::add_number(wt->js,"note_id"));
      } // End Fail block
      return callback_out;
    }
  };

  std::string j_str;
  auto *rt = (PdmRunTime *) rtt;
  std::map<std::string,std::string>
      data= PDM::pdm_net_type::getNoteRetrieveJsonStr(rt->wt.userinfo.sess
                                                      ,rt->wt.userinfo.email
                                                      , std::to_string(noteId)
                                                      , rt->notes.GetNoteType); // Should have note id
  j_str = PDM::network::get_json(data);
  QtConcurrent::run(PdmRunTime::post,j_str,rt->actions.notesGetHeadsURL,  &rt->wt,NetCallBack_::_callback);
  return 0;
}

void PDM::pdm_qt_net::client_action_note_create(PdmRunTime *rt) {
  emit rt->logc("Note create NOT IMPLEMENTED! ", "red");
}
/**
 * Encrypts the current note to be sent to the server. Then send to server.
 *
 * */
int PDM::pdm_qt_net::client_action_note_update(const PdmRunTime *rtt, PDM::NoteMsg msg) {
  struct NetCallBack_ {
    static size_t _callback(char *data, size_t size, size_t nmemb, void *userp) {
      int callback_out = (int) PDM::network::post_callback_update(data,  size,  nmemb, userp);
      auto *wt = (struct NetObj *)userp;
      auto*rt = (PdmRunTime *)wt->pdm_runtime;
      std::cout << "Note update callback finished and calling noteUpdateSuccess. " << std::endl;
      if (rt->wt.userinfo.status == "success") {
        int noteId = net_convert::get_int(wt->js,"note_id");
        std::cout << "Note update success: "<<noteId << std::endl;
        emit rt->noteUpdateSuccess(noteId );
      } // End Success block
      else { // Begin Fail block
        std::cout << "Note update failure: " << std::endl;
        emit rt->logc("Unsuccessful notes callback. ", "red");
        emit rt->noteUpdateFail(net_convert::add_number(wt->js,"note_id"));
      } // End Fail block
      return callback_out;
    }
  };

  std::string j_str;
  auto *rt = (PdmRunTime *) rtt;
  emit rt->logc_std("[Note update call] email: "+rt->wt.userinfo.email
    + ", sess: "+rt->wt.userinfo.sess
    + ", note_id: "+std::to_string((int)(*msg.note_id.c_str()))
    + ", head: "+msg.head
    + ", content: "+msg.content
    + ", update_type: "+rt->notes.UpdateNoteType
    + ", hash: "+get_hash(msg.content)
    , "red");
  std::map<std::string,std::string>
      data= PDM::pdm_net_type::getNoteUpdateJsonStr(
          rt->wt.userinfo.sess
          , rt->wt.userinfo.email
          , std::to_string((int)(*msg.note_id.c_str()))
          , rt->notes.UpdateNoteType
          , loader_check(rt->wt.data,msg.head)
          , loader_check(rt->wt.data,msg.content)
          , get_hash(msg.content)
          );
  j_str = PDM::network::get_json(data);
  QtConcurrent::run(PdmRunTime::post,j_str,rt->actions.notesGetHeadsURL,  &rt->wt,NetCallBack_::_callback);
  return 0;
}
