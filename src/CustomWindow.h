//
// Created by Yi Yang on 3/14/2023.
//

#ifndef PDM_QT_CUSTOMWINDOW_H
#define PDM_QT_CUSTOMWINDOW_H
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class CustomTitleBar : public QWidget {
  Q_OBJECT

public:
  explicit CustomTitleBar(QWidget *parent = nullptr);
  ~CustomTitleBar() override;
  QPushButton *customButton;

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
protected:
  void paintEvent(QPaintEvent *event) override;

};


#endif //PDM_QT_CUSTOMWINDOW_H
