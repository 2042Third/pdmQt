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
#include <QSplitter>
#include <QStackedWidget>
#include "settingsmenuWidget.h"
#include "others/tools/pdmQtWidgets.h"
#include "mainwindow.h"

settingsmenuWidget::settingsmenuWidget(QWidget *parent,PdmRunTime*rtIn ): QWidget(parent)
, PdmRuntimeRef(rtIn)
{
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  auto *splitter = new QSplitter(Qt::Horizontal, this);
  mainLayout->addWidget(splitter);

  auto* listWidget = new QListWidget(splitter);
  listWidget->setMaximumWidth(200);

  auto *stackedWidget = new QStackedWidget(splitter);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  stackedWidget->setSizePolicy(sizePolicy);
  stackedWidget->setMinimumWidth(200);

  splitter->addWidget(listWidget);
  splitter->addWidget(stackedWidget);
  connect(listWidget, &QListWidget::currentRowChanged,
          stackedWidget, &QStackedWidget::setCurrentIndex);
  // General settings
  listWidget->addItem("General");
  stackedWidget->addWidget(settingsGeneralSettings(this));
  // Security settings
  listWidget->addItem("Security");
  stackedWidget->addWidget(settingSecuritySettings(this));
  // Note Editor settings
  listWidget->addItem("Note Editor");
  stackedWidget->addWidget( settingsNoteEditor(this));


}

settingsmenuWidget::~settingsmenuWidget() {

}

QWidget *settingsmenuWidget::settingsGeneralSettings(settingsmenuWidget *pWidget) {

  QWidget*  widget= new QWidget(pWidget);
  QVBoxLayout* mainLayout = new QVBoxLayout(widget);


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

  PDM::addGridLayoutSpacer(gridLayout,2,0,1,2);

  gridLayout->addWidget(new QLabel("Option 3:"), 3, 0);
  gridLayout->addWidget(new QRadioButton("Enable"), 3, 1);

  QPushButton* okButton = new QPushButton("OK");
//  connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
  mainLayout->addWidget(okButton);
  return widget;
}

QWidget *settingsmenuWidget::settingSecuritySettings(settingsmenuWidget *pWidget) {
  QWidget* widget = new QWidget(pWidget);
  QGridLayout* gridLayout = new QGridLayout(widget);

  gridLayout->addWidget(new QLabel("Username In Status Bar:"), 0, 0);
  QCheckBox* checkBox = new QCheckBox("Enable");
  gridLayout->addWidget(checkBox, 0, 1);
  checkBox->setChecked(rt->getCmd("showUsernameInStatusBar"));
  connect(checkBox, &QCheckBox::clicked, [this](bool checked){
    rt->setCmd("showUsernameInStatusBar" ,checked); // Change the value
    rt->runCmd("showUsernameInStatusBar"); // Update using the custom actions
  });

  return widget;
}

QWidget *settingsmenuWidget::settingsNoteEditor(settingsmenuWidget *pWidget) {
  QWidget* widget = new QWidget(pWidget);
  QGridLayout* gridLayout = new QGridLayout(widget);

  return widget;
}

