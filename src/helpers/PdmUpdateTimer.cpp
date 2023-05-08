//
// Created by Yi Yang on 5/8/2023.
//

#include "PdmUpdateTimer.h"

PdmUpdateTimer::PdmUpdateTimer(QObject *parent) : QTimer(parent){
  setSingleShot(true);
}

PdmUpdateTimer::PdmUpdateTimer(int msec, QObject *parent) {
  setSingleShot(true);
  setInterval(msec);
}
