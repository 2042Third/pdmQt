//
// Created by Mike Yang on 2023/8/15.
//

#ifndef PDM_QT_FLASHINGCIRCLE_H
#define PDM_QT_FLASHINGCIRCLE_H


#include <QWidget>
#include <QPainter>

class FlashingCircle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int alpha READ alpha WRITE setAlpha)

public:
    explicit FlashingCircle(QWidget *parent = nullptr, int w=10, int h=10)
        : QWidget(parent), m_alpha(255) {
      setAttribute(Qt::WA_TranslucentBackground);
      setAttribute(Qt::WA_NoSystemBackground);
      setMinimumSize(QSize(w, h));
      setMaximumSize(QSize(w, h));
      show();
    }

    int alpha() const { return m_alpha; }

public slots:
        void setAlpha(int value)
    {
      m_alpha = value;
      update(); // Update the widget to redraw with the new alpha value
    }

protected:
    void paintEvent(QPaintEvent *)
    {
      QPainter painter(this);
      painter.setRenderHint(QPainter::Antialiasing);  // Enable anti-aliasing
      QColor color(255, 0, 0, m_alpha); // Red color with current alpha value
      painter.setBrush(color);
      painter.setPen(Qt::NoPen);  // Ensure there's no border pen
      painter.drawEllipse(rect()); // Draw a circle covering the entire widget's rectangle
    }

private:
    int m_alpha;
};


#endif //PDM_QT_FLASHINGCIRCLE_H
