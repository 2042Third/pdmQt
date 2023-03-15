//
// Created by Yi Yang on 3/15/2023.
//

#include "shadowFrameWidget.h"
#include <QPalette>

ShadowFrameWidget::ShadowFrameWidget(QWidget *parent) : QWidget(parent) {
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  setPalette(palette);
  setAutoFillBackground(true);
//  setStyleSheet("border-radius: 10px;");
}
