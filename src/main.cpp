/**
 * PDM Notes Desktop version with QT.
 * Made by Yi Yang
 * Jan. 2023
 *
 * */

#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName("PDM");
  QCoreApplication::setOrganizationDomain("pdm.pw");
  QCoreApplication::setApplicationName("PDMNotes");

  // Application Icon
  a.setWindowIcon(QIcon(":/images/icon/icon_small"));

  // Translation
  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "pdm_qt_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  MainWindow w;
  w.show();
  return a.exec();
}
