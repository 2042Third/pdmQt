//
// Created by Yi Yang on 5/8/2023.
//

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QAbstractButton>
#include "settingsmenuWidget.h"

settingsmenuWidget::settingsmenuWidget(QWidget *parent): QWidget(parent)
, PdmRuntimeRef()
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  QGridLayout* gridLayout = new QGridLayout;
  mainLayout->addLayout(gridLayout);

  gridLayout->addWidget(new QLabel("Option 1:"), 0, 0);
  gridLayout->addWidget(new QCheckBox("Enable"), 0, 1);

  QFrame* line1 = new QFrame;
  line1->setFrameShape(QFrame::HLine);
  line1->setFrameShadow(QFrame::Sunken);
  mainLayout->addWidget(line1);

  gridLayout->addWidget(new QLabel("Option 2:"), 1, 0);
  QComboBox* comboBox = new QComboBox;
  comboBox->addItem("Choice 1");
  comboBox->addItem("Choice 2");
  comboBox->addItem("Choice 3");
  gridLayout->addWidget(comboBox, 1, 1);

  QFrame* line2 = new QFrame;
  line2->setFrameShape(QFrame::HLine);
  line2->setFrameShadow(QFrame::Sunken);
  mainLayout->addWidget(line2);

  gridLayout->addWidget(new QLabel("Option 3:"), 2, 0);
  gridLayout->addWidget(new QRadioButton("Enable"), 2, 1);

  QPushButton* okButton = new QPushButton("OK");
//  connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
  mainLayout->addWidget(okButton);
}

settingsmenuWidget::~settingsmenuWidget() {

}

void settingsmenuWidget::setRef(PdmRunTime *rtRef) {
  PdmRuntimeRef::setRef(rtRef);
}
