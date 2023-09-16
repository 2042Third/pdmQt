//
// Created by 18604 on 9/16/2023.
//

#ifndef PDM_QT_DEBUGWINDOWCOMMANDWIDGET_H
#define PDM_QT_DEBUGWINDOWCOMMANDWIDGET_H
#include <QtWidgets>
#include <map>
#include <memory>
#include <algorithm>
#include "PdmRunTime.h"
#include "PdmRuntimeRef.h"

class CommandWidget : public QWidget,
public PdmRuntimeRef {
  Q_OBJECT
public:
  CommandWidget(QWidget* parent = nullptr,PdmRunTime*r=nullptr)
  : QWidget(parent),PdmRuntimeRef(r) {
    layout = new QVBoxLayout(this);

    lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);

    popupView = new QListView(this);
    popupView->setWindowFlags(Qt::Popup| Qt::FramelessWindowHint);
    model = new QStandardItemModel(this);
    popupView->setModel(model);

    connect(lineEdit, &QLineEdit::textChanged, this, &CommandWidget::onTextChanged);
    connect(popupView, &QListView::clicked, this, &CommandWidget::onItemClicked);

    // Populate commandMap with commands.
    // For example:
    // commandMap["cmd1"] = std::make_unique<Command>();
    // commandMap["cmd2"] = std::make_unique<Command>();
    // ...
  }

private slots:
  void onTextChanged(const QString& text) {
    model->clear();

    if (text.isEmpty()) {
      popupView->hide();
      return;
    }
    if (rt == nullptr) {
      popupView->hide();
      return;
    }

    // Go through the command map and find matching commands
    for (const auto& pair : rt->commandMap) {
      if (QString::fromStdString(pair.first).startsWith(text, Qt::CaseInsensitive)) {
        QStandardItem* item = new QStandardItem(QString::fromStdString(pair.first));
        model->appendRow(item);
      }
    }

    if (model->rowCount() == 0) {
      popupView->hide();
      return;
    }

    QPoint pos = lineEdit->mapToGlobal(lineEdit->rect().bottomLeft());
    popupView->setMinimumWidth(lineEdit->width());
    popupView->move(pos);
    popupView->show();
  }

  void onItemClicked(const QModelIndex &index) {
    QString selectedCommand = index.data().toString();
    lineEdit->setText(selectedCommand);
    popupView->hide();
  }

private:
  QVBoxLayout* layout;
  QLineEdit* lineEdit;
  QListView* popupView;
  QStandardItemModel* model;

};


#endif //PDM_QT_DEBUGWINDOWCOMMANDWIDGET_H
