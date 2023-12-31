//
// Created by Yi Yangs on 4/29/2023.
//

#ifndef PDM_QT_PDMLISTVIEW_H
#define PDM_QT_PDMLISTVIEW_H


#include <QListView>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QProxyStyle>
#include "PdmRunTimeRef.h"
#include "NotesScrollDelegate.h"
#include <QMenu>
class pdmListViewSortFilterProxyModel;

class pdmListView : public QListView, public PdmRunTimeRef
{
  Q_OBJECT
  public:
  explicit pdmListView(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);
public:
  pdmListViewSortFilterProxyModel *proxyModel;

private slots:
  void zoomingIn();
  void zoomingOut();

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void handleDeleteAction(const QModelIndex &index);
    void handleMoreAction(const QModelIndex &index);
    void handleRenameAction(const QModelIndex &index);
    void leaveEvent(QEvent *event) override;
    QMenu *contextMenu;
    QAction *deleteAction;
    QAction *moreAction;
    QAction *renameAction;
    NotesScrollDelegate *scrollDelegate;
private:
    QModelIndex lastHovered;
    QVariantAnimation *inAnimation;
    QVariantAnimation *outAnimation;

    void clearHover();
};


#endif //PDM_QT_PDMLISTVIEW_H
