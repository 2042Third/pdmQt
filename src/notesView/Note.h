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
  int noteid;

  Note(const QString &title, const QString &subtitle, const QDateTime &date, int note_id)
      : title(title), subtitle(subtitle), date(date), noteid(note_id) {}
};


#endif //PDM_QT_NOTE_H
