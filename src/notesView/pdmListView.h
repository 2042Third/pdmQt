//
// Created by Yi Yangs on 4/29/2023.
//

#ifndef PDM_QT_PDMLISTVIEW_H
#define PDM_QT_PDMLISTVIEW_H


#include <QListView>
#include <QMouseEvent>
#include "PdmRuntimeRef.h"

class pdmListView : public QListView, public PdmRuntimeRef
{
  Q_OBJECT
  public:
  explicit pdmListView(QWidget *parent = nullptr);


  protected:
  void mousePressEvent(QMouseEvent *event) override;
  void handleDeleteAction(const QModelIndex &index);
  void handleMoreAction(const QModelIndex &index);

};


#endif //PDM_QT_PDMLISTVIEW_H
