//
// Created by 18604 on 4/27/2023.
//

#ifndef PDM_QT_NOTE_H
#define PDM_QT_NOTE_H


#include <QString>
#include <QDateTime>

class Note {
public:
  QString title;
  QString subtitle;
  QDateTime date;

  Note(const QString &title, const QString &subtitle, const QDateTime &date)
      : title(title), subtitle(subtitle), date(date) {}
};


#endif //PDM_QT_NOTE_H
