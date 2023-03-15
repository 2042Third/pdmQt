//
// Created by Yi Yang on 3/15/2023.
//

#ifndef PDM_QT_SHADOWFRAMEWIDGET_H
#define PDM_QT_SHADOWFRAMEWIDGET_H
#include <QWidget>
#include <QPainter>

class ShadowFrameWidget : public QWidget {
Q_OBJECT

public:
  explicit ShadowFrameWidget(QWidget *parent = nullptr);

//protected:
//  void paintEvent(QPaintEvent *event) override;
};
#endif