//
// Created by Yi Yang on 4/29/2023.
//

#include "pdmListView.h"
#include "NotesScrollDelegate.h"
#include <QMenu>

pdmListView::pdmListView(QWidget *parent, PdmRunTime* rtIn) :
  QListView(parent)
  , PdmRuntimeRef(rtIn)
{
  setMouseTracking(true);
  scrollDelegate=new NotesScrollDelegate(this,rt);
  setItemDelegate(scrollDelegate);
  firstAction = new QAction("Delete", this);
  secondAction = new QAction("More", this);
  contextMenu = new QMenu(this);

  contextMenu->addAction(firstAction);
  contextMenu->addAction(secondAction);

  // Mouse in hover animation
  inAnimation = new QVariantAnimation(this);
  inAnimation->setStartValue(0.1);
  inAnimation->setEndValue(0.34);
  inAnimation->setDuration(80);
  connect(inAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
      if (lastHovered.isValid()) {
        qDebug()<<"inAnimation="+QString::number(value.toFloat());
        model()->setData(lastHovered, value, Qt::UserRole + 1);
        update(lastHovered);
      }
  });

  // Mouse out hover animation
  outAnimation = new QVariantAnimation(this);
  outAnimation->setStartValue(0.34);
  outAnimation->setEndValue(0.1);
  outAnimation->setDuration(60);
  connect(outAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
      if (lastHovered.isValid()) {
        qDebug()<<"outAnimation="+QString::number(value.toFloat());
        model()->setData(lastHovered, value, Qt::UserRole + 1);
        update(lastHovered);
      }
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
  if (index.isValid() && index != lastHovered) {
    clearHover();

    // Stop any ongoing out animation and start the in animation
    outAnimation->stop();
    lastHovered = index;
    inAnimation->start();
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
  clearHover();
  QListView::leaveEvent(event);
}

void pdmListView::clearHover()
{
  if (lastHovered.isValid()) {
    // Stop any ongoing in animation and start the out animation
    inAnimation->stop();
    outAnimation->start();

    model()->setData(lastHovered, 0.0, Qt::UserRole + 1);
  }
  lastHovered = QModelIndex();
}