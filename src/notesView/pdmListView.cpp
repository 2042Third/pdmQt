//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"

pdmListView::pdmListView(QWidget *parent) :
  QListView(parent)
  , PdmRuntimeRef()
{

}

void pdmListView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid())
        emit rt->noteListLeftClicked(index);
  } else if (event->button() == Qt::RightButton) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid())
        emit rt->noteListRightClicked(index);
  }
  QListView::mousePressEvent(event);
}