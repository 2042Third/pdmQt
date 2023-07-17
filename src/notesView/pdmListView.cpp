//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"
#include <QMenu>

pdmListView::pdmListView(QWidget *parent) :
  QListView(parent)
  , PdmRuntimeRef()
{
  firstAction = new QAction("Delete", this);
  secondAction = new QAction("More", this);
  contextMenu = new QMenu(this);

  contextMenu->addAction(firstAction);

  contextMenu->addAction(secondAction);
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
      disconnect(firstAction, &QAction::triggered, 0, 0); // Disconnect from previous slots
      disconnect(secondAction, &QAction::triggered, 0, 0); // Disconnect from previous slots

      // Connect to the current index
      connect(firstAction, &QAction::triggered, this, [this, index]() { handleDeleteAction(index); });
      connect(secondAction, &QAction::triggered, this, [this, index]() { handleMoreAction(index); });

      // Show the context menu at the event position
      contextMenu->exec(event->globalPos());
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
