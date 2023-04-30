//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"

pdmListView::pdmListView(QWidget *parent) : QListView(parent) {

}
void pdmListView::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid())
        emit leftClicked(index);
  } else if (event->button() == Qt::RightButton) {
    QModelIndex index = indexAt(event->pos());
    if (index.isValid())
        emit rightClicked(index);
  }
  QListView::mousePressEvent(event);
}