//
// Created by Yi Yang on 3/14/2023.
//

#ifndef PDM_QT_CUSTOMTITLEBAR_H
#define PDM_QT_CUSTOMTITLEBAR_H
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "helpers/PdmUpdateTimer.h"

class CustomTitleBar : public QWidget {
  Q_OBJECT

public:
  explicit CustomTitleBar(QWidget *parent = nullptr);
  ~CustomTitleBar() override;
  QPushButton *customButton;
  void changeName (QString a) ;

signals:
    void minimizeWindow();
    void maximizeWindow();
    void closeWindow();


private:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  QPoint m_dragStartPosition;
  bool m_dragging = false;

  QHBoxLayout *layout;
  QLabel *titleLabel;
  QPushButton *minimizeButton;
  QPushButton *maximizeButton;
  QPushButton *closeButton;

  // Dark gray button
  QString buttonStyleSheetDG = "QPushButton { border: none;padding: 5px; }"
                               "QPushButton:hover { background-color: #C4C4C4; }"
                               "QPushButton:pressed { background-color: #B2B2B2; }";
  // Red button
  QString buttonStyleSheetRD = "QPushButton { border: none;padding: 5px; }"
                               "QPushButton:hover { background-color: #F50000; }"
                               "QPushButton:pressed { background-color: #DE1F1F; }";
protected:
  PdmUpdateTimer *moveTimer;
  void onMoveTimerTimeout();

  bool event(QEvent *event) override;
};


#endif //PDM_QT_CUSTOMTITLEBAR_H
