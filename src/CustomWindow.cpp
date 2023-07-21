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
#include <QPalette>
#include <QOperatingSystemVersion>

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
  minimizeButton = new QPushButton("", this);
  maximizeButton = new QPushButton("", this);
  closeButton = new QPushButton("", this);

  if (QOperatingSystemVersion::currentType() == QOperatingSystemVersion::MacOS) {
    minimizeButton->setIcon(QIcon(":/images/icon/macMinimize"));
    maximizeButton->setIcon(QIcon(":/images/icon/macMaximize"));
    closeButton->setIcon(QIcon(":/images/icon/macClose"));

    closeButton->setStyleSheet("QPushButton { background-color: red; border-radius: 6px; }");
    minimizeButton->setStyleSheet("QPushButton { background-color: yellow; border-radius: 6px; }");
    maximizeButton->setStyleSheet("QPushButton { background-color: lime; border-radius: 6px; }");

    layout->addWidget(closeButton);
    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
  }
  else {
    minimizeButton->setIcon(QIcon(":/images/icon/minus"));
    maximizeButton->setIcon(QIcon(":/images/icon/maximize"));
    closeButton->setIcon(QIcon(":/images/icon/close"));

    minimizeButton->setStyleSheet("QPushButton { background-color: gray; }");
    maximizeButton->setStyleSheet("QPushButton { background-color: gray; }");
    closeButton->setStyleSheet("QPushButton { background-color: red; }");

    layout->addWidget(minimizeButton);
    layout->addWidget(maximizeButton);
    layout->addWidget(closeButton);
  }

  connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
  connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeWindow);
  connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);

  layout->addWidget(minimizeButton);
  layout->addWidget(maximizeButton);
  layout->addWidget(closeButton);

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