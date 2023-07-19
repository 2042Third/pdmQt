//
// Created by Yi Yangs on 4/29/2023.
//

#ifndef PDM_QT_PDMLISTVIEW_H
#define PDM_QT_PDMLISTVIEW_H


#include <QListView>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "PdmRuntimeRef.h"
#include "NotesScrollDelegate.h"

class pdmListView : public QListView, public PdmRuntimeRef
{
  Q_OBJECT
  public:
  explicit pdmListView(QWidget *parent = nullptr);


  protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void handleDeleteAction(const QModelIndex &index);
    void handleMoreAction(const QModelIndex &index);
    void leaveEvent(QEvent *event) override;
    QMenu *contextMenu;
    QAction *firstAction;
    QAction *secondAction;
    NotesScrollDelegate *scrollDelegate;
private:
    QModelIndex lastHovered;
    QVariantAnimation *animation;
};


#endif //PDM_QT_PDMLISTVIEW_H
