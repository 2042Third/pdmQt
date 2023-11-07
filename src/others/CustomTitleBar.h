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
  std::unique_ptr<QLabel >titleLabel;
  QPushButton *minimizeButton;
  QPushButton *maximizeButton;
  QPushButton *closeButton;

  // Dark gray button
  QString buttonStyleSheetDG_sq = "QPushButton { border: none;padding: 5px; }"
                               "QPushButton:hover { background-color: #C4C4C4; }"
                               "QPushButton:pressed { background-color: #B2B2B2; }";
    // Red button
    QString buttonStyleSheetRD_sq = "QPushButton { border: none;padding: 5px; }"
                                 "QPushButton:hover { background-color: #ED6A5E; }"
                                 "QPushButton:pressed { background-color: #F50000; }";
    // Yellow button, using grb (244,191,81)
    QString buttonStyleSheetYL_sq = "QPushButton { border: none;padding: 5px; }"
                                 "QPushButton:hover { background-color:  #F4BF4F; }"
                                 "QPushButton:pressed { background-color: #F5F500; }";
    // Green button
    QString buttonStyleSheetGR_sq = "QPushButton { border: none;padding: 5px; }"
                                 "QPushButton:hover { background-color: #62C554; }"
                                 "QPushButton:pressed { background-color: #5BC083; }";
    QString buttonStyleSheetDG = "QPushButton { width: 30px; height: 30px; border-radius: 15px; border: none; padding: 5px; }"
                                 "QPushButton:hover { background-color: #C4C4C4; }"
                                 "QPushButton:pressed { background-color: #B2B2B2; }";
// Red button
    QString buttonStyleSheetRD = "QPushButton { width: 12px; height: 12px; border-radius: 6px; border: none; background-color: #FF5F57; margin: 4px; }"
                                 "QPushButton:hover { background-color: #FF3B30; }"
                                 "QPushButton:pressed { background-color: #CC3727; }";
// Yellow button
    QString buttonStyleSheetYL = "QPushButton { width: 12px; height: 12px; border-radius: 6px; border: none; background-color: #FFBD2E; margin: 4px; }"
                                 "QPushButton:hover { background-color: #FFB627; }"
                                 "QPushButton:pressed { background-color: #CC943A; }";
// Green button
    QString buttonStyleSheetGR = "QPushButton { width: 12px; height: 12px; border-radius: 6px; border: none; background-color: #27C93F; margin: 4px; }"
                                 "QPushButton:hover { background-color: #15B233; }"
                                 "QPushButton:pressed { background-color: #10922C; }";



protected:
  PdmUpdateTimer *moveTimer;
  void onMoveTimerTimeout();

  bool event(QEvent *event) override;
};


#endif //PDM_QT_CUSTOMTITLEBAR_H
