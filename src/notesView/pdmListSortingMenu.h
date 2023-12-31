//
// Created by Yi Yang on 12/30/2023.
//

#ifndef PDM_QT_PDMLISTSORTINGMENU_H
#define PDM_QT_PDMLISTSORTINGMENU_H


#include <QWidget>

class pdmListSortingMenu : public QWidget {
  Q_OBJECT
public:
  pdmListSortingMenu();

private slots:
      void onSortOptionTriggered(QAction* action);

private:
  QMenu* sortMenu;
  QAction* actionSortByName;
  QAction* actionSortByCreateTime;
  QAction* actionSortByUpdateTime;
  QAction* actionDone;
  Qt::SortOrder sortOrder;
};


#endif //PDM_QT_PDMLISTSORTINGMENU_H
