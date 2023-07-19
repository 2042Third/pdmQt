//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"
#include "NotesScrollDelegate.h"
#include <QMenu>

pdmListView::pdmListView(QWidget *parent) :
  QListView(parent)
  , PdmRuntimeRef()
{
  setMouseTracking(true);
  scrollDelegate=new NotesScrollDelegate(this);
  setItemDelegate(scrollDelegate);
  scrollDelegate->setRef(rt);
  firstAction = new QAction("Delete", this);
  secondAction = new QAction("More", this);
  contextMenu = new QMenu(this);

  contextMenu->addAction(firstAction);
  contextMenu->addAction(secondAction);

  animation = new QVariantAnimation(this);
  animation->setStartValue(0.0);
  animation->setEndValue(1.0);
  animation->setDuration(140); // duration in ms, adjust to your liking

  connect(animation, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
      if (lastHovered.isValid()) {
        emit rt->log("Setting hover progress:" + QString::number(value.toFloat()) ,  "#000000");
        model()->setData(lastHovered, value, Qt::UserRole + 1);
        update(lastHovered);
      }
      this->viewport()->repaint();

  });

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

void pdmListView::mouseMoveEvent(QMouseEvent *event)
{
  QModelIndex index = indexAt(event->pos());
//  if (index.isValid())
//    update(index);

  QModelIndex hoveredIndex = indexAt(event->pos());
  if (index.isValid() && index != lastHovered) {
    emit rt->log("Hovering over item at row:" + QString::number(hoveredIndex.row()) ,  "#000000");
    emit rt->log("Data:" + hoveredIndex.data().toString() ,  "#000000");
    if (lastHovered.isValid())
      model()->setData(lastHovered, 0.0, Qt::UserRole + 1);
    lastHovered = index;
    animation->start();
    emit rt->log("Animation started" ,  "#000000");
  }
  QListView::mouseMoveEvent(event);
}

void pdmListView::handleDeleteAction(const QModelIndex &index) {
  emit rt->log("[Note action delete]  called " ,  "#000000");
}

void pdmListView::handleMoreAction(const QModelIndex &index) {
  emit rt->log("[Note action more]  called " ,  "#000000");

}

void pdmListView::leaveEvent(QEvent *event)
{
  if (lastHovered.isValid())
    model()->setData(lastHovered, 0.0, Qt::UserRole + 1);
  lastHovered = QModelIndex();
  animation->stop();
  QListView::leaveEvent(event);
}