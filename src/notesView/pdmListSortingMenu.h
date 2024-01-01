//
// Created by Yi Yang on 12/30/2023.
//

#ifndef PDM_QT_PDMLISTSORTINGMENU_H
#define PDM_QT_PDMLISTSORTINGMENU_H


#include <QWidget>
#include "PdmRunTimeRef.h"

class pdmListSortingMenu : public QWidget, public PdmRunTimeRef {
  Q_OBJECT
public:
  explicit pdmListSortingMenu( QWidget *parent = nullptr, PdmRunTime* rtIn = nullptr);
  void displaySortingMenu(const QPoint& pos);
private slots:
  void sortByName();
  void sortByCreateTime();
  void sortByUpdateTime();

private:
  QMenu* sortMenu;
  QAction* actionSortByName;
  QAction* actionSortByCreateTime;
  QAction* actionSortByUpdateTime;
  QAction* actionDone;
  Qt::SortOrder sortOrder;
};


#endif //PDM_QT_PDMLISTSORTINGMENU_H
