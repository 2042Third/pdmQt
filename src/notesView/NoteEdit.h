//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_NOTEEDIT_H
#define PDM_QT_NOTEEDIT_H


#include <QTextEdit>
#include "handler/types.h"

// Your NoteHead and NoteMsg struct declarations here

class NoteEdit : public QTextEdit {
Q_OBJECT

public:
  explicit NoteEdit(PDM::NoteMsg note, QWidget *parent = nullptr) ;
  explicit NoteEdit( QWidget *parent = nullptr) ;

  // Accessor methods to get and set the NoteMsg object
  PDM::NoteMsg* getNote() {return &m_note;}

  void setNote(const PDM::NoteMsg &note) {
    m_note = note;
    // Update the QTextEdit content when the note is changed
    setPlainText(QString::fromStdString(m_note.content));
  }

  void setNote(){ setPlainText(m_note.content.c_str());}

private:
  PDM::NoteMsg m_note;
};


#endif //PDM_QT_NOTEEDIT_H
