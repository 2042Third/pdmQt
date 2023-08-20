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
      animateAlpha(startValue, midValue, endValue, animation);
      animationDuration(duration, animation);
      animation->setEasingCurve(QEasingCurve::InOutSine); // Smooth easing curve
      animation->setLoopCount(-1); // Loop indefinitely
      animation->setLoopCount(loopCount);
      return animation;
    }

    static void animateAlpha(int startValue, int midValue, int endValue, void *animation) {
      auto * ani = static_cast<QPropertyAnimation*>(animation);
      ani->setStartValue(startValue);
      ani->setEndValue(endValue);
      ani->setKeyValueAt(0.5, midValue); // At halfway point, be fully opaque
    }

    static void animationDuration(int duration, void *animation) {
      static_cast<QPropertyAnimation*>(animation)->setDuration(duration);
    }

    static void* animationStop(void* animation){
      static_cast<QPropertyAnimation*>(animation)->stop();
      return animation;
    }
    static void* animationStart(void* animation){
      static_cast<QPropertyAnimation*>(animation)->start();
      return animation;
    }




};
#endif //PDM_QT_ANIMATED_H
