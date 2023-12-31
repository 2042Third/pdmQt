//
// Created by Yi Yang  on 12/30/2023.
//

#include <QModelIndex>
#include "pdmListViewSortFilterProxyModel.h"
#include "handler/types.h"
#include "notesView/NotesScroll.h"

pdmListViewSortFilterProxyModel::pdmListViewSortFilterProxyModel(QObject *parent, PdmRunTime* rtIn)
    : QSortFilterProxyModel(parent), PdmRunTimeRef(rtIn), sortColumn(SortColumn::NoteCreateTime), sortOrder(Qt::AscendingOrder) {}

void pdmListViewSortFilterProxyModel::setSortingCriteria(SortColumn column, Qt::SortOrder order) {
  sortColumn = column;
  sortOrder = order;
  invalidate(); // This will trigger a re-sort
}

bool pdmListViewSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {

  const PDM::NoteHead &leftNote = rt->noteList->notesList[left.row()];
  const PDM::NoteHead &rightNote = rt->noteList->notesList[right.row()];
  bool result = false;
  switch (sortColumn) {
    case NoteName:
      // Compare based on NoteName
      if (!(leftNote.head.empty() || rightNote.head.empty())) {
        result = comp(leftNote.head, rightNote.head);
      }
      break;
    case NoteCreateTime:
      // Compare based on NoteCreateTime
      result = comp(leftNote.ctime, rightNote.ctime);
      break;
    case NoteUpdateTime:
      // Compare based on NoteUpdateTime
      result = comp(leftNote.time, rightNote.time);
      break;
    default:
      // Default sorting is note creation time
      result = comp(leftNote.ctime, rightNote.ctime);
      break;
  }
  return result;
}

bool pdmListViewSortFilterProxyModel::comp(const std::string &left, const std::string &right) const {
  if (sortOrder == Qt::AscendingOrder) {
    return left < right;
  } else {
    return left > right;
  }
}

bool pdmListViewSortFilterProxyModel::comp(const double left, const double right) const {
  if (sortOrder == Qt::AscendingOrder) {
    return left < right;
  } else {
    return left > right;
  }
}
