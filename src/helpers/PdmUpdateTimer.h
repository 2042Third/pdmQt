//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_PDMUPDATETIMER_H
#define PDM_QT_PDMUPDATETIMER_H


#include <QTimer>
/**
 * Connect to "PdmUpdateTimer::timeout()" signal to handle the timeout event.
 *
 * Use start() to start the timer.
 * If before the timer is reached, start() is called again, the timer will be reset.
 * */
class PdmUpdateTimer: public QTimer {
public:
  explicit PdmUpdateTimer(QObject *parent = nullptr);
  explicit PdmUpdateTimer(int msec, QObject *parent = nullptr);
};


#endif //PDM_QT_PDMUPDATETIMER_H
