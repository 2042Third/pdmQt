//
// Created by Mike Yang on 2023/8/17.
//

#ifndef PDM_QT_PDMQTWIDGETS_H
#define PDM_QT_PDMQTWIDGETS_H

#include <QWidget>
#include <QListWidget>
#include <QAbstractButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <sys/socket.h>

namespace PDM{
    QListWidgetItem* listSeparator(){
      auto *separator = new QListWidgetItem();
      separator->setBackground(Qt::gray); // or any other color to make it look like a separator
      separator->setSizeHint(QSize(separator->sizeHint().width(), 2));  // reduce height
      return separator;
    }

    QWidget* addCollapsibleFrame (const QString&name,QLayout*layout, QWidget*widget) {

      // Create a tool button for toggling collapse
      auto *toggleButton = new QToolButton(widget);
      toggleButton->setArrowType(Qt::ArrowType::DownArrow);
      toggleButton->setMaximumSize(10,10);


      auto *labelWidget = new QWidget(widget);
      auto *labelLayout = new QHBoxLayout(labelWidget);
      auto *buttonLabel = new QLabel(name,widget);
      labelLayout->addWidget(buttonLabel);
      labelLayout->addWidget(toggleButton);
      layout->addWidget(labelWidget);

      // Create a frame as the collapsible content
      auto *collapsibleFrame = new QFrame(widget);
      collapsibleFrame->setFrameShape(QFrame::Panel);
      collapsibleFrame->setFrameShadow(QFrame::Sunken);
      layout->addWidget(collapsibleFrame);

      // By default, the content is visible
      collapsibleFrame->setVisible(false);

      // Connect the button's signal to toggle visibility
      QAbstractButton::connect(toggleButton, &QToolButton::clicked, [toggleButton, collapsibleFrame](){
          collapsibleFrame->setVisible(!collapsibleFrame->isVisible());
          if(collapsibleFrame->isVisible()) {
            toggleButton->setArrowType(Qt::ArrowType::DownArrow);
          } else {
            toggleButton->setArrowType(Qt::ArrowType::RightArrow);
          }
      });
      return collapsibleFrame;
    }
}
#endif //PDM_QT_PDMQTWIDGETS_H
