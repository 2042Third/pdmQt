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

#define PDM_USE_FRAMELESSHELPER

#ifdef PDM_USE_FRAMELESSHELPER
#include <FramelessHelper/Widgets/framelessmainwindow.h>
#include <FramelessHelper/Core/private/framelessconfig_p.h>
#endif

int main(int argc, char *argv[])
{

#ifdef PDM_USE_FRAMELESSHELPER
  wangwenx190::FramelessHelper::FramelessHelper::Widgets::initialize();
#endif
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
#ifdef PDM_USE_FRAMELESSHELPER
  {
    FRAMELESSHELPER_USE_NAMESPACE
    FramelessHelper::Core::setApplicationOSThemeAware();
    // Not setting the blur behind due to inconsistency.
    FramelessConfig::instance()->set(Global::Option::EnableBlurBehindWindow);
  }
#endif
  // Initialization done, start app.
  MainWindow w;
  w.show();

  return a.exec();
}
