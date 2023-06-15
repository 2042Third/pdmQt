//
// Created by Yi Yang on 3/15/2023.
//

#include "shadowFrameWidget.h"
#include <QPalette>
#include <QApplication>
#include <QEvent>

ShadowFrameWidget::ShadowFrameWidget(QWidget *parent) : QWidget(parent) {
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::white);
  setPalette(palette);
  setAutoFillBackground(true);
//  setStyleSheet("border-radius: 10px;");
}

bool ShadowFrameWidget::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::PaletteChange: {
      // The application palette has changed
      // Update your widget's colors here

      QPalette palette = QApplication::palette();
      // You may want to use different color roles depending on what part of the widget you are updating
      QColor backgroundColor = palette.color(QPalette::Window);

      // Assuming your custom title bar has a solid background color, you can update it like this:
      QPalette shadowFramePalette = this->palette();
      shadowFramePalette.setColor(QPalette::Window, backgroundColor);
      this->setPalette(shadowFramePalette);
      this->setAutoFillBackground(true);
      break;
    }
    default: {
      break;
    }
  }

  return QWidget::event(event);
}
