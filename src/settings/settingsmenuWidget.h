//
// Created by Yi Yang on 5/8/2023.
//

#ifndef PDM_QT_SETTINGSMENUWIDGET_H
#define PDM_QT_SETTINGSMENUWIDGET_H


#include <QWidget>
#include "PdmRunTimeRef.h"

class settingsmenuWidget : public QWidget, public PdmRunTimeRef
{
  Q_OBJECT
public:
  explicit settingsmenuWidget(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
  ~settingsmenuWidget();

  QWidget *settingsGeneralSettings(settingsmenuWidget *pWidget);

  QWidget *settingSecuritySettings(settingsmenuWidget *pWidget);

  QWidget *settingsNoteEditor(settingsmenuWidget *pWidget);
};


#endif //PDM_QT_SETTINGSMENUWIDGET_H
