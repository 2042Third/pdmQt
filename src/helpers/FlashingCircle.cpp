//
// Created by Mike Yang on 2023/8/17.
//
#include "FlashingCircle.h"
#include <iostream>

QStringList FlashingCircle::colorNames = QColor::colorNames();

FlashingCircle::FlashingCircle(QWidget *parent , int w, int h)
: QWidget(parent){
  color = new QColor();
  setColor("red");
  setAttribute(Qt::WA_TranslucentBackground);
  setAttribute(Qt::WA_NoSystemBackground);
  setMinimumSize(QSize(w, h));
  setMaximumSize(QSize(w, h));
  show();
}

FlashingCircle::~FlashingCircle() {
  delete color;
}

void FlashingCircle::setAlpha(int value)
{
  if (color->alpha() != value)
  {
    color->setAlpha(value);
    update();  // this will trigger paintEvent to be called
  }
}

void FlashingCircle::setColor(int qt_global_color){
  if (qt_global_color >= 0 && qt_global_color < colorNames.size()) {
    PDM::Helpers::QtColor::copy_rgb(
        QColor::fromString(colorNames.at(qt_global_color)),
        color);
  }
}

void FlashingCircle::setColor(const QString&colorName){
  if (colorNames.contains(colorName)) {
    PDM::Helpers::QtColor::copy_rgb(
        QColor::fromString(colorName),
        color);
  }
}

void FlashingCircle::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);  // Enable anti-aliasing
  painter.setBrush(*color);
  painter.setPen(Qt::NoPen);  // Ensure there's no border pen
  painter.drawEllipse(rect()); // Draw a statusCircle covering the entire widget's rectangle
}

