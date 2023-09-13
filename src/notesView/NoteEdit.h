//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_NOTEEDIT_H
#define PDM_QT_NOTEEDIT_H


#include <QTextEdit>
#include "handler/types.h"
#include "PdmRuntimeRef.h"
#include "helpers/PdmUpdateTimer.h"

// Your NoteHead and NoteMsg struct declarations here

class NoteEdit : public QTextEdit , public PdmRuntimeRef{
Q_OBJECT

public:
  explicit NoteEdit(PDM::NoteMsg note, QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr) ;
  explicit NoteEdit( QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr) ;
  ~NoteEdit() ;

  void clearNoteMsg(PDM::NoteMsg& noteMsg) ;
  PDM::NoteMsg* getNote() {return &m_note;}// Accessor methods to get and set the NoteMsg object
  void setNote(const PDM::NoteMsg &note) {
    m_note = note;
    setPlainText(QString::fromStdString(m_note.content));// Update the QTextEdit content when the note is changed
  }

  void setNote(){ setPlainText(m_note.content.c_str());}
  PDM::NoteMsg m_note;

  int idx=0;
  double getFontSize(){return fontSize;}
  double fontSize=12;

  private slots:
  void zoomingIn();
  void zoomingOut();

private:
  PdmUpdateTimer* updateTimer;

  void clearEditText();

  void updateFontSize();
};


#endif //PDM_QT_NOTEEDIT_H
