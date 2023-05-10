//
// Created by Yi Yang on 4/27/2023.
//

#include "NotesScroll.h"

NotesScroll::NotesScroll(QObject *parent) : QAbstractListModel(parent) {

}

void NotesScroll::addNote( PDM::NoteHead note)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_notes << note;
  endInsertRows();
}

int NotesScroll::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent)
  return m_notes.count();
}
QVariant NotesScroll::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= m_notes.count())
    return QVariant();

  const PDM::NoteHead &note = m_notes[index.row()];
  if (role == Qt::DisplayRole) {
    return QString::fromStdString(note.head + "\n" + "\n" + note.ctime);
  } else if (role == Qt::UserRole) {
    return QString::fromStdString(note.ctime);
  }
  return QVariant();
}

const PDM::NoteHead* NotesScroll::getNote(const QModelIndex &index) const {
  if (index.row() < 0 || index.row() >= m_notes.size())
    return nullptr; // Return a nullptr if the index is invalid

  return &m_notes[index.row()];
}
