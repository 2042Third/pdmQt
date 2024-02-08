//
// Created by Yi Yang  on 12/30/2023.
//

#include <QModelIndex>
#include "pdmListViewSortFilterProxyModel.h"
#include "handler/types.h"
#include "notesView/NotesScroll.h"

pdmListViewSortFilterProxyModel::pdmListViewSortFilterProxyModel( PdmRunTime* rtIn)
    : QSortFilterProxyModel(), PdmRunTimeRef(rtIn), sortColumn(SortColumn::NoteCreateTime), sortOrder(Qt::AscendingOrder) {
  connect(rt, &PdmRunTime::noteListSortingOption, this, &pdmListViewSortFilterProxyModel::sortFilterNoteListSortingOption);
}

void pdmListViewSortFilterProxyModel::setSortingCriteria(SortColumn column, Qt::SortOrder order) {
  sortColumn = column;
  sortOrder = order;
  invalidate(); // This will trigger a re-sort
  sort(0); // Explicitly trigger sorting
}

bool pdmListViewSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
  emit rt->logc_std("Comparison lessThan called", "blue");

  const PDM::NoteHead &leftNote = rt->noteList->notesMap[rt->noteList->notesList[left.row()]];
  const PDM::NoteHead &rightNote = rt->noteList->notesMap[rt->noteList->notesList[right.row()]];
  emit rt->logc_std("Comparison lessThan called, leftNote.head: " + leftNote.note_id + ", rightNote.head: " + rightNote.note_id, "blue");

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
      emit rt->logc_std("Comparison update time between "+ std::to_string(leftNote.time) + " and " + std::to_string(rightNote.time) +
                        ", result ="+std::to_string(result), "blue");
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

void
pdmListViewSortFilterProxyModel::sortFilterNoteListSortingOption(int columnInt) {
  SortColumn columnIn;
  emit rt->logc_std("pdmListViewSortFilterProxyModel::sortFilterNoteListSortingOption, columnInt: " + std::to_string(columnInt), "blue");
  switch (columnInt) {
    case 1:
      columnIn = NoteName;
      break;
    case 2:
      columnIn = NoteCreateTime;
      break;
    case 3:
      columnIn = NoteUpdateTime;
      break;
    default:
      columnIn = NoteCreateTime;
      break;
  }

  // Toggle the sort order if the same option is selected again
  if (sortColumn == columnIn) {
    sortOrder = (sortOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
  } else {
    sortOrder = Qt::AscendingOrder;
    sortColumn = columnIn;
  }
  // Apply the sorting criteria to your model
  setSortingCriteria(sortColumn, sortOrder);
  emit rt->noteListUpdate();
}
