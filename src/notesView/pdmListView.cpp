//
// Created by Yi Yang on 4/29/2023.
//

#include <QSettings>
#include "pdmListView.h"
#include "NotesScrollDelegate.h"

pdmListView::pdmListView(QWidget *parent, PdmRunTime* rtIn) :
  QListView(parent)
  , PdmRuntimeRef(rtIn)
{
  setMouseTracking(true);
  scrollDelegate=new NotesScrollDelegate(this,rt); // Create the delegate (how the list items are drawn)
  setItemDelegate(scrollDelegate); // Sets this delegate as the painter for the list items
  firstAction = new QAction("Delete", this); // Right click menu item delete
  secondAction = new QAction("More", this); // Right click menu item more
  contextMenu = new QMenu(this); // The right click menu
  // Remove the space in front of each menu item
  // , so that the icon is flush with the left edge.
  contextMenu->setStyleSheet("QMenu::item { padding-left: 10px; padding-top: 3px; padding-right: 10px; padding-bottom: 3px; }"
                             "QMenu::item:selected { background-color: #1787FF; }");  // Change to your preferred color

  contextMenu->addAction(firstAction);
  contextMenu->addAction(secondAction);

  // Mouse in hover animation
  inAnimation = new QVariantAnimation(this);
  inAnimation->setStartValue(0.1);
  inAnimation->setEndValue(0.34);
  inAnimation->setDuration(80);
  connect(inAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
      if (lastHovered.isValid()) {
//        qDebug()<<"inAnimation="+QString::number(value.toFloat());
        model()->setData(lastHovered, value, Qt::UserRole + 1);
        update(lastHovered);
      }
  });

  // Mouse out hover animation
  outAnimation = new QVariantAnimation(this);
  outAnimation->setStartValue(0.34);
  outAnimation->setEndValue(0.1);
  outAnimation->setDuration(90);
  connect(outAnimation, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
      if (lastHovered.isValid()) {
        model()->setData(lastHovered, value, Qt::UserRole + 1);
        update(lastHovered);
      }
  });

//  connect(rt, &PdmRunTime::onZoomIn, this, &pdmListView::zoomingIn);
//  connect(rt, &PdmRunTime::onZoomOut, this, &pdmListView::zoomingOut);

  // Get the font size from the settings
  QSettings settings;
  scrollDelegate->primaryFontSizeCache=settings.value("pdmListView/primaryFontSize", 12).toDouble();
  scrollDelegate->secondaryFontSizeCache=settings.value("pdmListView/secondaryFontSize", 12).toDouble();
  scrollDelegate->setFontSize(scrollDelegate->primaryFontSizeCache,scrollDelegate->secondaryFontSizeCache);

  // Set smooth scrolling
  setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);


  viewport()->update();
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

void pdmListView::zoomingIn() {
  scrollDelegate->setFontSize(scrollDelegate->primaryFontSizeCache+2,scrollDelegate->secondaryFontSizeCache+2);
  viewport()->update();
  QSettings settings;
  settings.setValue("pdmListView/primaryFontSize", scrollDelegate->primaryFontSizeCache);
  settings.setValue("pdmListView/secondaryFontSize", scrollDelegate->secondaryFontSizeCache);
}

void pdmListView::zoomingOut() {
  scrollDelegate->setFontSize(scrollDelegate->primaryFontSizeCache-2,scrollDelegate->secondaryFontSizeCache-2);
  viewport()->update();
  QSettings settings;
  settings.setValue("pdmListView/primaryFontSize", scrollDelegate->primaryFontSizeCache);
  settings.setValue("pdmListView/secondaryFontSize", scrollDelegate->secondaryFontSizeCache);
}
