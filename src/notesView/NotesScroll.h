//
// Created by Yi Yang on 4/27/2023.
//

#ifndef PDM_QT_NOTESSCROLL_H
#define PDM_QT_NOTESSCROLL_H


#include <QAbstractListModel>
#include "handler/types.h"

class NotesScroll : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit NotesScroll(QObject *parent = nullptr);
  void addNote( PDM::NoteHead note);
  const PDM::NoteHead* getNote(const QModelIndex &index)const ;
  int rowCount(const QModelIndex & parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  QList<PDM::NoteHead> m_notes;
};


#endif //PDM_QT_NOTESSCROLL_H
