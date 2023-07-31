//
// Created by Yi Yang on 3/15/2023.
//

#include "shadowFrameWidget.h"
#include <QPalette>
#include <QApplication>
#include <QEvent>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

ShadowFrameWidget::ShadowFrameWidget(QWidget *parent) : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint) {
  setAttribute(Qt::WA_TranslucentBackground);

  QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
  effect->setBlurRadius(10);
  effect->setXOffset(0);
  effect->setYOffset(0);
  effect->setColor(Qt::black);
  setGraphicsEffect(effect);

  setAutoFillBackground(false);
}

void ShadowFrameWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing); // Enable anti-aliasing

  QPainterPath path;
  path.addRoundedRect(rect().adjusted(5, 5, -5, -5), 10, 10); // Adjust the rect so that the shadow effect won't be cut off

  painter.fillPath(path, Qt::white); // Fill the path with color
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
