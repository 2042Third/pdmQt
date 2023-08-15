//
// Created by Mike Yang on 2023/8/15.
//

#ifndef PDM_QT_ANIMATED_H
#define PDM_QT_ANIMATED_H

#include <QWidget>
#include <QPropertyAnimation>

class Animated {
public:
    static void makeAnimateAlpha(QObject * wgt, QObject * parent = nullptr){
      auto *animation = new QPropertyAnimation(wgt, "alpha",parent);
      animation->setDuration(4000); // Duration of 2 seconds
      animation->setStartValue(0);  // Starting from fully transparent
      animation->setEndValue(0);  // Going to fully transparent
      animation->setKeyValueAt(0.5, 255); // At halfway point, be fully opaque
      animation->setEasingCurve(QEasingCurve::InOutSine); // Smooth easing curve
      animation->setLoopCount(-1); // Loop indefinitely
      animation->start();
    }
};
#endif //PDM_QT_ANIMATED_H
