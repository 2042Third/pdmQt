//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_NOTEEDIT_H
#define PDM_QT_NOTEEDIT_H


#include <QTextEdit>
#include "handler/types.h"
#include "PdmRuntimeRef.h"

// Your NoteHead and NoteMsg struct declarations here

class NoteEdit : public QTextEdit , public PdmRuntimeRef{
Q_OBJECT

public:
  explicit NoteEdit(PDM::NoteMsg note, QWidget *parent = nullptr) ;
  explicit NoteEdit( QWidget *parent = nullptr) ;
  ~NoteEdit() ;

  void clearNoteMsg(PDM::NoteMsg& noteMsg) ;
  PDM::NoteMsg* getNote() {return &m_note;}// Accessor methods to get and set the NoteMsg object
  void setNote(const PDM::NoteMsg &note) {
    m_note = note;
    setPlainText(QString::fromStdString(m_note.content));// Update the QTextEdit content when the note is changed
  }

  void setNote(){ setPlainText(m_note.content.c_str());}

private:
  PDM::NoteMsg m_note;

  void clearEditText();
};


#endif //PDM_QT_NOTEEDIT_H
