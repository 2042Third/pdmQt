//
// Created by Mike Yang on 2023/8/15.
//

#ifndef PDM_QT_ANIMATED_H
#define PDM_QT_ANIMATED_H

#include <QWidget>
#include <QPropertyAnimation>

class Animated {
public:
    static QPropertyAnimation* makeAnimateAlpha(QObject * wgt, QObject * parent = nullptr
        , int startValue = 0, int endValue = 0, int duration = 4000, int loopCount = -1
            , int midValue = 255
        ){
      auto *animation = new QPropertyAnimation(wgt, "alpha", parent);
      animation->setStartValue(startValue);
      animation->setEndValue(endValue);
      animation->setDuration(duration);
      animation->setKeyValueAt(0.5, midValue); // At halfway point, be fully opaque
      animation->setEasingCurve(QEasingCurve::InOutSine); // Smooth easing curve
      animation->setLoopCount(-1); // Loop indefinitely
      animation->setLoopCount(loopCount);
      return animation;
    }

    static QPropertyAnimation* animationStop(QPropertyAnimation* animation){
      animation->stop();
      return animation;
    }




};
#endif //PDM_QT_ANIMATED_H
