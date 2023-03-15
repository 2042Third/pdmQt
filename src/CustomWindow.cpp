//
// Created by Yi Yang on 3/14/2023.
//
#include <QMouseEvent>
#include <QStyleFactory>
#include <QApplication>
#include <QPainter>
#include <QStyleOption>
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

CustomTitleBar::~CustomTitleBar() {
  delete layout;
  delete titleLabel;
  delete customButton;
  delete minimizeButton;
  delete maximizeButton;
  delete closeButton;
}

CustomTitleBar::CustomTitleBar(QWidget *parent)
    : QWidget(parent) {

  // Create a horizontal layout for the custom title bar
  layout = new QHBoxLayout(this);
  layout->setContentsMargins(5, 5, 5, 5);
  layout->setSpacing(5);

  // Create a QLabel for the window title
  titleLabel = new QLabel("Custom Window", this);
  layout->addWidget(titleLabel);

  // Create a custom button for the title bar
  customButton = new QPushButton("", this);
//  connect(customButton, &QPushButton::clicked, this, &CustomTitleBar::on_customButton_clicked);
  layout->addWidget(customButton);

  // Add spacer to push the custom button to the right side
  layout->addStretch(1);

  // Create the minimize, maximize, and close buttons
  minimizeButton = new QPushButton("", this); minimizeButton->setIcon(QIcon(":/images/icon/minus"));
  maximizeButton = new QPushButton("", this); maximizeButton->setIcon(QIcon(":/images/icon/maximize"));
  closeButton = new QPushButton(QIcon(":/images/icon/close"),"", this);

  connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
  connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);
  connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);

  layout->addWidget(minimizeButton);
  layout->addWidget(maximizeButton);
  layout->addWidget(closeButton);

}

void CustomTitleBar::paintEvent(QPaintEvent *event)
{
//  QPainter painter(this);
//  painter.setRenderHint(QPainter::Antialiasing);
//
//  QStyleOption opt;
//  opt.initFrom(this);
//  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
//
//  QColor color(0, 0, 0, 50);
//  for (int i = 1; i <= 10; i++) {
//    painter.setPen(QPen(color, i, Qt::SolidLine, Qt::RoundCap));
//    painter.drawRoundedRect(QRectF(i, i, width() - 2 * i, height() - 2 * i), 5, 5);
//  }
}
