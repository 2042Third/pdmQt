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
#include "PdmRunTimeRef.h"
#include "handler/pdm_qt_helpers.h"

#define SETTING_STRING_EMITTER_BLUE(x) \
  emit rt->log((x+"="+std::to_string(rt->commandMap[x]->getValue())).c_str(), "#0000FF");

class CommandWidget : public QWidget,
public PdmRunTimeRef {
  Q_OBJECT
public:
  CommandWidget(QWidget* parent = nullptr,PdmRunTime*r=nullptr)
  : QWidget(parent), PdmRunTimeRef(r) {
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
            if(runAllCommands(PDM::pdm_qt_helpers::splitString(command.toStdString(),','))){
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

  int runAllCommands(std::vector<std::string> commands){

    for (const std::string& segment : commands) {
      int rtr = rt->run(segment);
      if ( rtr == -1){
        SETTING_STRING_EMITTER_BLUE(segment);
      }
      if(rtr == 0 ){
        emit rt->log("Command not found: "+QString::fromStdString(segment), "#FF0004");
      }
    }
    return 1;
  }

private:
  QVBoxLayout* layout;
  QLineEdit* lineEdit;

};


#endif //PDM_QT_DEBUGWINDOWCOMMANDWIDGET_H
