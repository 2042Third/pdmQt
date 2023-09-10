//
// Created by Mike Yang on 2023/8/17.
//

#ifndef PDM_QT_PDMQTWIDGETS_H
#define PDM_QT_PDMQTWIDGETS_H

#include <QWidget>
#include <QListWidget>
#include <QAbstractButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QMouseEvent>
#include "pdmExtraQtWidgets.h"

#ifdef __APPLE__
#include <sys/socket.h>
#endif // __APPLE__

namespace PDM {

  QListWidgetItem* listSeparator();

  QWidget* addCollapsibleFrame(const QString& name, QLayout* layout, QWidget* widget);

  QFrame* addGridLayoutSpacer(QGridLayout* layout, int row, int col, int rowSpan, int colSpan);

} // namespace PDM

#endif //PDM_QT_PDMQTWIDGETS_H
