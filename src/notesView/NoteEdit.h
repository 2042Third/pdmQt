//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_NOTEEDIT_H
#define PDM_QT_NOTEEDIT_H


#include <QTextEdit>
#include "handler/types.h"
#include "PdmRunTimeRef.h"
#include "helpers/PdmUpdateTimer.h"

// Your NoteHead and NoteMsg struct declarations here

class NoteEdit : public QTextEdit , public PdmRunTimeRef{
Q_OBJECT

public:
  explicit NoteEdit(PDM::NoteMsg note, QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr) ;
  explicit NoteEdit( QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr) ;
  ~NoteEdit() ;

  void clearNoteMsg(PDM::NoteMsg& noteMsg) ;
  PDM::NoteMsg* getNote() {return &note_edit;}// Accessor methods to get and set the NoteMsg object
  void setNote(const PDM::NoteMsg &note) {
    note_edit = note;
    setPlainText(QString::fromStdString(note_edit.content));// Update the QTextEdit content when the note is changed
  }

  void updateContentToStorage();
  void setNote();
  PDM::NoteMsg note_edit;

  int idx=0;
  double getFontSize(){return fontSize;}
  int fontSize=12;
  int openedNoteId = -1;

  private slots:
  void zoomingIn();
  void zoomingOut();

private:
  PdmUpdateTimer* updateTimer;

  void clearEditText();

  void updateFontSize();

};


#endif //PDM_QT_NOTEEDIT_H
