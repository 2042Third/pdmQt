//
// Created by Mike Yang on 2023/8/17.
//

#ifndef PDM_QT_PDMEXTRAQTWIDGETS_H
#define PDM_QT_PDMEXTRAQTWIDGETS_H

#include <QWidget>
#include <QMouseEvent>

namespace PDM::ExtraQt{
    class ClickableWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit ClickableWidget(QWidget* parent = nullptr) : QWidget(parent) {}

        signals:
            void clicked();

    protected:
        void mousePressEvent(QMouseEvent* event) override {
          if (event->button() == Qt::LeftButton) {
            emit clicked();
          }
          QWidget::mousePressEvent(event);
        }
    };
}
#endif //PDM_QT_PDMEXTRAQTWIDGETS_H
