//
// Created by Yi Yang on 3/14/2023.
//
#include <QMouseEvent>
#include <QStyleFactory>
#include <QApplication>
#include <QPainter>
#include <QStyleOption>
#include <QSettings>
#include "CustomTitleBar.h"
#include <QTimer>
#include <QPalette>
#include <QOperatingSystemVersion>
#include <Global>

#define USING_MACOS_FRAMELESS_HELPER 1

CustomTitleBar::CustomTitleBar(QWidget *parent)
    : QWidget(parent) {

  // Create a horizontal layout for the custom title bar
  layout = new QHBoxLayout(this);
  layout->setContentsMargins(5, 0, 5, 0);
  layout->setSpacing(5);

  // Create a custom button for the title bar
  customButton = new QPushButton("", this);

  // Create the minimize, maximize, and close buttons
  if (QOperatingSystemVersion::currentType() == QOperatingSystemVersion::MacOS && !USING_MACOS_FRAMELESS_HELPER) {
    // Set the size of the buttons
    QSize buttonSize(12, 12);

    // Set the size of the icons
    QSize iconSize(10, 10);  // Adjust as necessary

    minimizeButton = new QPushButton("", this);
    minimizeButton->setIcon(QIcon(":/images/icon/minus"));
    minimizeButton->setIconSize(iconSize);
    minimizeButton->setFlat(true);
    minimizeButton->setStyleSheet(buttonStyleSheetYL);

    maximizeButton = new QPushButton("", this);
    maximizeButton->setIcon(QIcon(":/images/icon/maximize"));
    maximizeButton->setIconSize(iconSize);
    maximizeButton->setFlat(true);
    maximizeButton->setStyleSheet(buttonStyleSheetGR);

    closeButton = new QPushButton("", this);
    closeButton->setIcon(QIcon(":/images/icon/close"));
    closeButton->setIconSize(iconSize);
    closeButton->setFlat(true);
    closeButton->setStyleSheet(buttonStyleSheetRD);

    layout->addWidget(closeButton);
    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);

// Add spacer to push the custom button to the left side
    layout->addStretch(1);
    layout->addWidget(customButton);
    layout->addWidget(titleLabel);
  } else if (USING_MACOS_FRAMELESS_HELPER) {
//    layout->addStretch(1);
    layout->addWidget(customButton);
    setStyleSheet(FRAMELESSHELPER_STRING_LITERAL(R"(
QMenuBar {
    background-color: transparent;
}

QMenuBar::item {
    background: transparent;
}

QMenuBar::item:selected {
    background: #a8a8a8;
}

QMenuBar::item:pressed {
    background: #888888;
}
    )"));
//    layout->addWidget(titleLabel);
  } else {
    layout->addWidget(customButton);

    // Add spacer to push the custom button to the right side
    layout->addStretch(1);

    minimizeButton = new QPushButton("", this);
    minimizeButton->setIcon(QIcon(":/images/icon/minus"));
    minimizeButton->setFlat(true);
    minimizeButton->setStyleSheet(buttonStyleSheetDG_sq);
    maximizeButton = new QPushButton("", this);
    maximizeButton->setIcon(QIcon(":/images/icon/maximize"));
    maximizeButton->setFlat(true);
    maximizeButton->setStyleSheet(buttonStyleSheetDG_sq);
    closeButton = new QPushButton(QIcon(":/images/icon/close"), "", this);
    closeButton->setFlat(true);
    closeButton->setStyleSheet(buttonStyleSheetRD_sq);

    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
    layout->addWidget(closeButton);
  }
  if(!USING_MACOS_FRAMELESS_HELPER){
    connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
    connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);
    connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);
  }



  moveTimer = new PdmUpdateTimer(3000, this);
  connect(moveTimer, &PdmUpdateTimer::timeout, this, &CustomTitleBar::onMoveTimerTimeout);
}

CustomTitleBar::~CustomTitleBar() {
  delete layout;
  delete titleLabel;
  delete customButton;
  delete minimizeButton;
  delete maximizeButton;
  delete closeButton;
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

void CustomTitleBar::changeName(QString a) {
  titleLabel->setText(a);
}

void CustomTitleBar::onMoveTimerTimeout() {
  QSettings settings;
  settings.setValue("debugwindow/positionX", window()->pos().x());
  settings.setValue("debugwindow/positionY", window()->pos().y());
}

bool CustomTitleBar::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::PaletteChange: {
      // The application palette has changed
      // Update your widget's colors here

      QPalette palette = QApplication::palette();
      // You may want to use different color roles depending on what part of the widget you are updating
      QColor backgroundColor = palette.color(QPalette::Window);
      QColor textColor = palette.color(QPalette::WindowText);

      // Assuming your custom title bar has a solid background color, you can update it like this:
      QPalette titleBarPalette = this->palette();
      titleBarPalette.setColor(QPalette::Window, backgroundColor);
      this->setPalette(titleBarPalette);
      this->setAutoFillBackground(true);

      // You can update the text color of the title label like this:
      QPalette labelPalette = titleLabel->palette();
      labelPalette.setColor(QPalette::WindowText, textColor);
      titleLabel->setPalette(labelPalette);

      // Similarly, you can update the colors of the buttons here
      // ...

      break;
    }
    default: {
      break;
    }
  }
  // Don't forget to call the base class implementation of the event method
  return QWidget::event(event);
}