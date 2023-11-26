//
// Created by Yi Yang on 4/27/2023.
//

#include <QAbstractItemView>
#include "NotesScroll.h"

NotesScroll::NotesScroll(QObject *parent) :
  QAbstractListModel(parent)
{

}

/**
 * Adds a note's copy to the list of notes.
 * If the note already exists, update using new data.
 * @param note The note to add
 * */
void NotesScroll::addNote( PDM::NoteHead note)
{
  if(notesMap.contains(note.note_id)){
    notesMap.insert(note.note_id,note); // If the note already exists, replace it

    // Find the index of the existing note in the list
    int indexToUpdate = notesList.indexOf(note);

    // Update the note in the list
    if (indexToUpdate != -1) {
      notesList[indexToUpdate] = note;

      // Emit the dataChanged signal to update the view
      QModelIndex topLeft = createIndex(indexToUpdate, 0);
      QModelIndex bottomRight = createIndex(indexToUpdate, 0);
      emit dataChanged(topLeft, bottomRight);
    }
    return;
  }
  notesMap.insert(note.note_id,note); // If the note already exists, replace it
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  notesList << note;
  endInsertRows();
}

int NotesScroll::rowCount(const QModelIndex & parent) const
{
  Q_UNUSED(parent)
  return notesList.count();
}
QVariant NotesScroll::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= notesList.count())
    return QVariant();

  const PDM::NoteHead &note = notesList[index.row()];
  if (role == Qt::DisplayRole) {
    if (note.head.empty()  ){
      return QString::fromStdString("Unnamed Note "+ note.note_id + "\n" + "\n" + note.ctime);
    }
    return QString::fromStdString(note.head + "\n" + "\n" + note.ctime);
  }
  else if (role == Qt::UserRole) {
    return QString::fromStdString(note.ctime);
  }
  else if (role == Qt::UserRole + 1) {
    return alphaProgress[index.row()];
  }
  return QVariant();
}

const PDM::NoteHead* NotesScroll::getNote(const QModelIndex &index) const {
  if (index.row() < 0 || index.row() >= notesList.size())
    return nullptr; // Return a nullptr if the index is invalid

  return &notesList[index.row()];
}

bool NotesScroll::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (role == Qt::UserRole + 1) {
    // Set the data for UserRole + 1
    alphaProgress.insert(index.row(), value);
    emit dataChanged(index, index, {role});
    return true;
  }
  return QAbstractListModel::setData(index, value, role);
}

void NotesScroll::clear() {
  beginResetModel();
  notesList.clear();
  notesMap.clear();
  endResetModel();
}

size_t NotesScroll::size() const {
  return notesList.size();
}

void NotesScroll::locateNote(const std::string &noteId) {
  // Find the note in the list
  int index = notesList.indexOf(notesMap[noteId]);

  // If the note is found, emit the dataChanged signal to update the view
  if (index != -1) {
    QModelIndex topLeft = createIndex(index, 0);
    QModelIndex bottomRight = createIndex(index, 0);
//    QModelIndex index = listModel->index(row, column); // row and column of the item
    scrollTo(index, QListView::PositionAtTop); // Scroll to make the item at the top

    emit dataChanged(topLeft, bottomRight);
  }
}

