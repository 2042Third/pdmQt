//
// Created by Yi Yang on 5/8/2023.
//

#include "NoteEdit.h"

#include <utility>

NoteEdit::NoteEdit(PDM::NoteMsg note, QWidget *parent):
QTextEdit(parent),
m_note(std::move(note)) {
  // Initialize your QTextEdit with the note content if needed
  setPlainText(QString::fromStdString(m_note.content));
}

NoteEdit::NoteEdit(QWidget *parent) :QTextEdit(parent){

}

