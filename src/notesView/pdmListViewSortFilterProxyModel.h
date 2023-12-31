//
// Created by Yi Yang on 12/30/2023.
//

#ifndef PDM_QT_PDMLISTVIEWSORTFILTERPROXYMODEL_H
#define PDM_QT_PDMLISTVIEWSORTFILTERPROXYMODEL_H


#include <QSortFilterProxyModel>
#include "PdmRunTimeRef.h"

class pdmListViewSortFilterProxyModel : public QSortFilterProxyModel, public PdmRunTimeRef {
public:
  enum SortColumn {
    NoteName,
    NoteCreateTime,
    NoteUpdateTime
    // Add other sorting criteria as needed
  };

  explicit pdmListViewSortFilterProxyModel(QObject *parent = nullptr, PdmRunTime* rtIn = nullptr);

  // Update the method signature to use SortColumn
  void setSortingCriteria(SortColumn column, Qt::SortOrder order);

protected:
  bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private slots:
  void sortFilterNoteListSortingOption(const SortColumn &columnIn);
private:
  bool comp(const std::string &left, const std::string &right) const;
  bool comp(const double left, const double right) const;
  SortColumn sortColumn;
  Qt::SortOrder sortOrder;
};


#endif //PDM_QT_PDMLISTVIEWSORTFILTERPROXYMODEL_H
