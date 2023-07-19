//
// Created by Yi Yang on 5/8/2023.
//

#include "NoteEdit.h"

#include <utility>

NoteEdit::NoteEdit(PDM::NoteMsg note, QWidget *parent, PdmRunTime* rtIn):
QTextEdit(parent)
, m_note(std::move(note))
, PdmRuntimeRef(rtIn)
{
  // Initialize your QTextEdit with the note content if needed
  setPlainText(QString::fromStdString(m_note.content));

  // Connect to the PDM runtime zoom in and zoom out signals
  connect(rt, &PdmRunTime::onZoomIn, this, &NoteEdit::zoomingIn);
  connect(rt, &PdmRunTime::onZoomOut, this, &NoteEdit::zoomingOut);

}

NoteEdit::NoteEdit(QWidget *parent, PdmRunTime* rtIn) :QTextEdit(parent){

}

NoteEdit::~NoteEdit(){
  clearNoteMsg(m_note);
  clearEditText();
}

void NoteEdit::clearNoteMsg(PDM::NoteMsg& noteMsg) {
  noteMsg.head.assign(noteMsg.head.length(), 0);
  noteMsg.note_id.assign(noteMsg.note_id.length(), 0);
  noteMsg.uid = -1;
  noteMsg.time = -1;
  noteMsg.update_time = -1;
  noteMsg.utime.assign(noteMsg.utime.length(), 0);
  noteMsg.ctime.assign(noteMsg.ctime.length(), 0);
  noteMsg.key = -1;
  noteMsg.content.assign(noteMsg.content.length(), 0);
  noteMsg.email.assign(noteMsg.email.length(), 0);
  noteMsg.session.assign(noteMsg.session.length(), 0);
  noteMsg.ntype.assign(noteMsg.ntype.length(), 0);
  noteMsg.sess.assign(noteMsg.sess.length(), 0);
  noteMsg.h.assign(noteMsg.h.length(), 0);
  noteMsg.username.assign(noteMsg.username.length(), 0);
  noteMsg.status.assign(noteMsg.status.length(), 0);
  noteMsg.statusInfo.assign(noteMsg.statusInfo.length(), 0);
  noteMsg.encry.assign(noteMsg.encry.length(), 0);
  noteMsg.hash.assign(noteMsg.hash.length(), 0);
}

void NoteEdit::clearEditText() {
  setPlainText(QString(toPlainText().size(),'0'));
}

void NoteEdit::zoomingIn() {
  this->zoomIn(2);
}

void NoteEdit::zoomingOut() {
  this->zoomOut(2);
}


