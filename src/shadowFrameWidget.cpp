//
// Created by Yi Yang on 3/15/2023.
//

#include "shadowFrameWidget.h"

ShadowFrameWidget::ShadowFrameWidget(QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_TranslucentBackground);
}

void ShadowFrameWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QColor shadowColor(0, 0, 0, 100); // Adjust the color and opacity as needed

  for (int i = 0; i < 10; ++i) { // Adjust the number of iterations to control the shadow size
    QRect shadowRect(rect());
    shadowRect.adjust(i, i, -i, -i);
    shadowColor.setAlpha(100 - qSqrt(i) * 50);
    painter.setPen(shadowColor);
    painter.drawRoundedRect(shadowRect, 10, 10);
  }

  QWidget::paintEvent(event);
}