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
#include "handler/pdm_qt_helpers.h"

class CommandWidget : public QWidget,
public PdmRuntimeRef {
  Q_OBJECT
public:
  CommandWidget(QWidget* parent = nullptr,PdmRunTime*r=nullptr)
  : QWidget(parent),PdmRuntimeRef(r) {
    layout = new QVBoxLayout(this);

    lineEdit = new QLineEdit(this);
    layout->addWidget(lineEdit);

    QStringList commandList;
    if (rt){
      for (const auto& pair : rt->commandMap) {
        commandList << QString::fromStdString(pair.first);
      }
    }
    QStringListModel *commandListModel = new QStringListModel(commandList, this);
    QCompleter *completer = new QCompleter(commandListModel, this);

    lineEdit->setCompleter(completer);
    lineEdit->installEventFilter(this);
  }
protected:
  bool eventFilter(QObject *obj, QEvent *event) override {
    if (obj == lineEdit) {
      if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return) {
          QString command = lineEdit->text();
          if (rt){ // Runs command if it is in the command map
            if(rt->run(PDM::pdm_qt_helpers::splitString(command.toStdString(),','))){
              emit rt->log(command, "#000000");
              lineEdit->clear();
              return true;
            }
          }

        }
      }
    }
    return QObject::eventFilter(obj, event);
  }

private:
  QVBoxLayout* layout;
  QLineEdit* lineEdit;

};


#endif //PDM_QT_DEBUGWINDOWCOMMANDWIDGET_H
