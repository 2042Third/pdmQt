//
// Created by Yi Yangs on 4/29/2023.
//

#ifndef PDM_QT_PDMLISTVIEW_H
#define PDM_QT_PDMLISTVIEW_H


#include <QListView>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QProxyStyle>
#include "PdmRuntimeRef.h"
#include "NotesScrollDelegate.h"
#include <QMenu>


class pdmListView : public QListView, public PdmRuntimeRef
{
  Q_OBJECT
  public:
  explicit pdmListView(QWidget *parent = nullptr, PdmRunTime* rtIn=nullptr);

private slots:
  void zoomingIn();
  void zoomingOut();

  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void handleDeleteAction(const QModelIndex &index);
    void handleMoreAction(const QModelIndex &index);
    void leaveEvent(QEvent *event) override;
    QMenu *contextMenu;
    QAction *deleteAction;
    QAction *moreAction;
    NotesScrollDelegate *scrollDelegate;
private:
    QModelIndex lastHovered;
    QVariantAnimation *inAnimation;
    QVariantAnimation *outAnimation;

    void clearHover();
};


#endif //PDM_QT_PDMLISTVIEW_H
