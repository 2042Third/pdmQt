//
// Created by Yi Yang on 12/30/2023.
//

#include "pdmListSortingMenu.h"
#include "pdmListViewSortFilterProxyModel.h"
#include <QMenu>
#include "notesView/NotesScroll.h"

pdmListSortingMenu::pdmListSortingMenu(QWidget *parent, PdmRunTime *rtIn) :
    QWidget(parent),PdmRunTimeRef(rtIn) {
// Initialize the sort order
      sortOrder = Qt::AscendingOrder;

      // Create the menu and actions
      sortMenu = new QMenu("Sort Options", this);

      actionSortByName = sortMenu->addAction("Sort by Note Name");
      actionSortByCreateTime = sortMenu->addAction("Sort by Creation Time");
      actionSortByUpdateTime = sortMenu->addAction("Sort by Update Time");
      sortMenu->addSeparator();
      actionDone = sortMenu->addAction("Done");

      // Connect actions to a slot
      connect(actionSortByName, &QAction::triggered, this, &::pdmListSortingMenu::sortByName);
      connect(actionSortByCreateTime, &QAction::triggered, this, &::pdmListSortingMenu::sortByCreateTime);
      connect(actionSortByUpdateTime, &QAction::triggered, this, &::pdmListSortingMenu::sortByUpdateTime);
      connect(actionDone, &QAction::triggered, sortMenu, &QMenu::hide);

  }

void pdmListSortingMenu::sortByName() {
  emit rt->noteListSortingOption(pdmListViewSortFilterProxyModel::NoteName);
}

void pdmListSortingMenu::sortByCreateTime() {
  emit rt->noteListSortingOption(pdmListViewSortFilterProxyModel::NoteCreateTime);
}

void pdmListSortingMenu::sortByUpdateTime() {
  emit rt->noteListSortingOption(pdmListViewSortFilterProxyModel::NoteUpdateTime);
}


