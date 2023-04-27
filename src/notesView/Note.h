//
// Created by 18604 on 4/27/2023.
//

#ifndef PDM_QT_NOTE_H
#define PDM_QT_NOTE_H


#include <QString>

class Note {
public:
  std::string title;
  std::string subtitle;
  std::string date;

  Note(const std::string &title, const std::string &subtitle, const std::string &date)
      : title(title), subtitle(subtitle), date(date) {}
};


#endif //PDM_QT_NOTE_H
