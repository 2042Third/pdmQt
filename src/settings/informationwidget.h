#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QWidget>
#include "PdmRunTimeRef.h"

namespace Ui {
class InformationWidget;
}

class InformationWidget : public QWidget,public PdmRunTimeRef
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
    ~InformationWidget();

private:
    Ui::InformationWidget *ui;
};

#endif // INFORMATIONWIDGET_H
