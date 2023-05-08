//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_PDMUPDATETIMER_H
#define PDM_QT_PDMUPDATETIMER_H


#include <QTimer>

class PdmUpdateTimer: public QTimer {
public:
  explicit PdmUpdateTimer(QObject *parent = nullptr);
  explicit PdmUpdateTimer(int msec, QObject *parent = nullptr);
};


#endif //PDM_QT_PDMUPDATETIMER_H
