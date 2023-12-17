//
// Created by Mike Yang on 2023/8/17.
//

#include "pdmQtHelpers.h"


void PDM::Helpers::QtColor::copy_rgb(const QColor &from, QColor *to) {
  to->setRed(from.red());
  to->setGreen(from.green());
  to->setBlue(from.blue());
}

QString PDM::Helpers::QtColor::get_color_rgb(const QString&colorName) {
  QString color_rgb = "";
  int color_index=QColor::colorNames().indexOf(colorName);
  if (color_index > -1) {
    auto color = QColor::fromString(colorName);
    // Turn QColor to rgb string in format of "#FFFFFF"
    color_rgb = QString("#%1%2%3")
        .arg(color.red(), 2, 16, QLatin1Char('0'))
        .arg(color.green(), 2, 16, QLatin1Char('0'))
        .arg(color.blue(), 2, 16, QLatin1Char('0'));
  }

  return color_rgb;
}

/**
 * Convert a std::string to lower case
 * @param str the string to be converted
 * @return the converted string
 * */
std::string PDM::Helpers::to_lower_std_string(const std::string &str) {
  std::string str_lower = str;
  std::transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
  return str_lower;
}
