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
  explicit NotesScroll(QObject *parent = nullptr);

  void addNote(const Note &note);

  int rowCount(const QModelIndex & parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
  QList<Note> m_notes;
};


#endif //PDM_QT_NOTESSCROLL_H
