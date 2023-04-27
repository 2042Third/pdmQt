//
// Created by Yi Yang on 4/27/2023.
//

#ifndef PDM_QT_NOTESSCROLL_H
#define PDM_QT_NOTESSCROLL_H


#include <QAbstractListModel>
#include "Note.h"

class NotesScroll : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit NotesScroll(QObject *parent = nullptr)
  : QAbstractListModel(parent) {}

  void addNote(const Note &note)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_notes << note;
    endInsertRows();
  }

  int rowCount(const QModelIndex & parent = QModelIndex()) const override
  {
    Q_UNUSED(parent)
    return m_notes.count();
  }

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
  {
    if (index.row() < 0 || index.row() >= m_notes.count())
      return QVariant();

    const Note &note = m_notes[index.row()];
    if (role == Qt::DisplayRole) {
      return note.title + "\n" + note.subtitle + "\n" + note.date.toString("yyyy-MM-dd hh:mm:ss");
    } else if (role == Qt::UserRole) {
      return note.date;
    }
    return QVariant();
  }

private:
  QList<Note> m_notes;
};


#endif //PDM_QT_NOTESSCROLL_H
