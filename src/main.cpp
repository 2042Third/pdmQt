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
#include <QSvgRenderer>

#include <FramelessHelper/Widgets/framelessmainwindow.h>

#include <FramelessHelper/Core/private/framelessconfig_p.h>
int main(int argc, char *argv[])
{

  wangwenx190::FramelessHelper::FramelessHelper::Widgets::initialize();
  QApplication a(argc, argv);

  QCoreApplication::setOrganizationName("pdm");
  QCoreApplication::setOrganizationDomain("pdm.pw");
  QCoreApplication::setApplicationName("pdmnotes");

  // Application Icon
  QSvgRenderer renderer;
  renderer.load(QString(":/images/icon/pdmIcon"));
  QPixmap pixmap(128, 128);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);
  painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
  renderer.render(&painter);
  QIcon icon(pixmap);

  a.setWindowIcon(icon);

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
  {
    FRAMELESSHELPER_USE_NAMESPACE
    FramelessHelper::Core::setApplicationOSThemeAware();

    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
  }
  // Initialization done, start app.
  MainWindow w;
  w.show();

  return a.exec();
}
