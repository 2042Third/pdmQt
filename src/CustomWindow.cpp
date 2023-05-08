//
// Created by Yi Yang on 3/14/2023.
//
#include <QMouseEvent>
#include <QStyleFactory>
#include <QApplication>
#include <QPainter>
#include <QStyleOption>
#include <QSettings>
#include "CustomWindow.h"
#include <QTimer>

CustomTitleBar::CustomTitleBar(QWidget *parent)
    : QWidget(parent) {

  // Create a horizontal layout for the custom title bar
  layout = new QHBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  // Create a QLabel for the window title
  titleLabel = new QLabel("Custom Window", this);
  titleLabel->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(titleLabel);

  // Create a custom button for the title bar
  customButton = new QPushButton("", this);
//  connect(customButton, &QPushButton::clicked, this, &CustomTitleBar::on_customButton_clicked);
  layout->addWidget(customButton);

  // Add spacer to push the custom button to the right side
  layout->addStretch(1);

  // Create the minimize, maximize, and close buttons
  minimizeButton = new QPushButton("", this); minimizeButton->setIcon(QIcon(":/images/icon/minus"));
  minimizeButton->setFlat(true); minimizeButton->setStyleSheet(buttonStyleSheetDG);
  maximizeButton = new QPushButton("", this); maximizeButton->setIcon(QIcon(":/images/icon/maximize"));
  maximizeButton->setFlat(true); maximizeButton->setStyleSheet(buttonStyleSheetDG);
  closeButton = new QPushButton(QIcon(":/images/icon/close"),"", this);
  closeButton->setFlat(true); closeButton->setStyleSheet(buttonStyleSheetRD);

  connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
  connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);
  connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);

  layout->addWidget(minimizeButton);
  layout->addWidget(maximizeButton);
  layout->addWidget(closeButton);

  moveTimer = new PdmUpdateTimer(3000, this);
  connect(moveTimer, &PdmUpdateTimer::timeout, this, &CustomTitleBar::onMoveTimerTimeout);
}


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
    moveTimer->start();
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


void CustomTitleBar::changeName(QString a) {
  titleLabel->setText(a);
}

void CustomTitleBar::onMoveTimerTimeout() {
  QSettings settings;
  settings.setValue("debugwindow/positionX", window()->pos().x());
  settings.setValue("debugwindow/positionY", window()->pos().y());
}
