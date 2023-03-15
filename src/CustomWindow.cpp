//
// Created by Yi Yang on 3/14/2023.
//
#include <QMouseEvent>

#include "CustomWindow.h"
void CustomTitleBar::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_dragStartPosition = event->globalPosition().toPoint();
    m_dragging = true;
  }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event) {
  if (m_dragging && (event->buttons() & Qt::LeftButton)) {
    QPoint delta = event->globalPosition().toPoint() - m_dragStartPosition;
    m_dragStartPosition = event->globalPosition().toPoint();
    window()->move(window()->pos() + delta);
  }
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_dragging = false;
  }
}