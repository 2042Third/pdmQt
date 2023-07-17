//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"
#include <QMenu>

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
    if (index.isValid()) {
      emit rt->noteListRightClicked(index);
      QMenu contextMenu(this);

      // Create menu actions
      QAction *firstAction = new QAction("Delete", this);
      connect(firstAction, &QAction::triggered, this, [this, index]() { handleDeleteAction(index); });
      contextMenu.addAction(firstAction);

      QAction *secondAction = new QAction("More", this);
      connect(secondAction, &QAction::triggered, this, [this, index]() { handleMoreAction(index); });
      contextMenu.addAction(secondAction);

      // Add more actions as required...

      // Display the context menu at the event position
      contextMenu.exec(event->globalPos());
    }
  }
  QListView::mousePressEvent(event);
}

void pdmListView::handleDeleteAction(const QModelIndex &index) {
  emit rt->log("[Note action delete]  called " ,  "#000000");
}

void pdmListView::handleMoreAction(const QModelIndex &index) {
  emit rt->log("[Note action more]  called " ,  "#000000");

}
