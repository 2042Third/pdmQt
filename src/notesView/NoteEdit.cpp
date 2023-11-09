//
// Created by Yi Yang on 5/8/2023.
//

#include "NoteEdit.h"
#include "others/tools/pdmQtHelpers.h"

#include <utility>
#include <QSettings>

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

  // Get the font size from the settings
  QSettings settings;
  fontSize=settings.value("NoteEdit/fontSize", 12).toInt();
  QFont font = this->font();
  font.setPointSize(fontSize);
  this->setFont(font);

  updateTimer = new PdmUpdateTimer(1300, rt);
  connect(updateTimer, &PdmUpdateTimer::timeout, this, [this](){
    // Update the note content when the text is changed
    m_note.content = toPlainText().toStdString(); // TODO: fix this whole update but change back to original situation.
    // Update the note content in the database
    rt->updateNoteContent(m_note);
    emit rt->logc("NoteEdit: update note content", "red");
    // Show the save complete animation
    rt->showSaveCompleteAnimation();
  });

  // Connect to the qtextedit text changed signal
  connect(this, &QTextEdit::textChanged, this, [this](){
    // Start the timer when the text is changed
    updateTimer->start();
    // Show pending animation
    rt->showPendingAnimation();
  });
}

NoteEdit::~NoteEdit() {
  clearNoteMsg(m_note);
  clearEditText();
  delete updateTimer;
}

NoteEdit::NoteEdit(QWidget *parent, PdmRunTime* rtIn) :QTextEdit(parent){

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
  fontSize = fontSize + 1;
  updateFontSize();
  QFont font = this->font();
  font.setPointSize(fontSize);
  emit rt->log("[NoteEdit Zoom In]  fontSize: " + QString::number(fontSize)
      ,  PDM::Helpers::QtColor::get_color_rgb("red"));
  this->setFont(font);
}

void NoteEdit::zoomingOut() {
  fontSize = fontSize - 1;
  updateFontSize();
  QFont font = this->font();
  font.setPointSize(fontSize);
  emit rt->log("[NoteEdit Zoom Out]  fontSize: " + QString::number(fontSize)
      ,  PDM::Helpers::QtColor::get_color_rgb("red"));
  this->setFont(font);
}

void NoteEdit::updateFontSize() {
  QSettings settings;
  emit rt->log("[NoteEdit]  fontSize: " + QString::number(fontSize)
               ,  PDM::Helpers::QtColor::get_color_rgb("red"));
  settings.setValue("NoteEdit/fontSize", fontSize);
}

void NoteEdit::setNote() {
  // Put the current content of the editor into a string
  if (toPlainText() != m_note.content.c_str() ){
    setPlainText(m_note.content.c_str());
  }
}


