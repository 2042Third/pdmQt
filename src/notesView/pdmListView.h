//
// Created by Yi Yangs on 4/29/2023.
//

#ifndef PDM_QT_PDMLISTVIEW_H
#define PDM_QT_PDMLISTVIEW_H


#include <QListView>
#include <QMouseEvent>

class pdmListView : public QListView
{
  Q_OBJECT
  public:
  explicit pdmListView(QWidget *parent = nullptr);

  signals:
  void leftClicked(const QModelIndex &index);
  void rightClicked(const QModelIndex &index);

  protected:
  void mousePressEvent(QMouseEvent *event) override;

};


#endif //PDM_QT_PDMLISTVIEW_H
