//
// Created by Yi Yang on 4/27/2023.
//

#ifndef PDM_QT_NOTESSCROLL_H
#define PDM_QT_NOTESSCROLL_H


#include <QAbstractListModel>
#include "handler/types.h"

class NotesScroll : public QAbstractListModel{
  Q_OBJECT

public:
  explicit NotesScroll(QObject *parent = nullptr);
  void addNote( PDM::NoteHead note);
  const PDM::NoteHead* getNote(const QModelIndex &index)const ;
  int rowCount(const QModelIndex & parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  void clear();
  size_t size() const;
  void locateNote(const std::string& noteId);

  QList<PDM::NoteHead> notesList;
  QMap<std::string,PDM::NoteHead> notesMap;
  QMap<int,QVariant>  alphaProgress ;
signals:
  void noteAdded(int index); // Signal to be emitted when a new note is added

};


#endif //PDM_QT_NOTESSCROLL_H
