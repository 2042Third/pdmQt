//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_SETTINGSMENUWIDGET_H
#define PDM_QT_SETTINGSMENUWIDGET_H


#include <QWidget>
#include "PdmRuntimeRef.h"

class settingsmenuWidget : public QWidget, public PdmRuntimeRef
{
  Q_OBJECT
public:
  explicit settingsmenuWidget(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~settingsmenuWidget();

  QWidget *settingsGeneralSettings(settingsmenuWidget *pWidget);
};


#endif //PDM_QT_SETTINGSMENUWIDGET_H
