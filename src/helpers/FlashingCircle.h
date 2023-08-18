//
// Created by Mike Yang on 2023/8/15.
//

#ifndef PDM_QT_FLASHINGCIRCLE_H
#define PDM_QT_FLASHINGCIRCLE_H


#include <QWidget>
#include <QPainter>
#include "src/others/tools/pdmQtHelpers.h"

class FlashingCircle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int alpha READ alpha WRITE setAlpha)

public:
    explicit FlashingCircle(QWidget *parent = nullptr, int w=10, int h=10);
    ~FlashingCircle() override;

    int alpha() const { return color->alpha(); }

public slots:
    void setAlpha(int value);
    void setColor(int qt_global_color);
    void setColor(const QString &colorName);
    [[nodiscard]] const QString& getColorName() const;


protected:
    void paintEvent(QPaintEvent *) override;

private:
    qsizetype currentColorIndex = 0;
    static QStringList colorNames;
    QColor *color = nullptr;

};


#endif //PDM_QT_FLASHINGCIRCLE_H
