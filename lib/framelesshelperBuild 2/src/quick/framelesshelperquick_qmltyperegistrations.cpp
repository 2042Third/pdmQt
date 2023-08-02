/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <framelesshelperquick_global.h>
#include <framelessquickapplicationwindow_p.h>
#include <framelessquickhelper.h>
#include <framelessquickutils.h>
#include <framelessquickwindow_p.h>
#include <quickchromepalette.h>
#include <quickimageitem.h>
#include <quickmicamaterial.h>
#include <quickstandardsystembutton_p.h>
#include <quickstandardtitlebar_p.h>
#include <quickwindowborder.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_org_wangwenx190_FramelessHelper()
{
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::FramelessQuickApplicationWindow>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickApplicationWindow, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickWindowQmlImpl, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickWindow, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QWindow, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::FramelessQuickHelper>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickItem, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::FramelessQuickUtils>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::FramelessQuickWindow>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickChromePalette>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickGlobal>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickImageItem>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickMicaMaterial>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickStandardSystemButton>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickAbstractButton, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterAnonymousType<QQuickControl, 254>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickStandardTitleBar>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterTypesAndRevisions<wangwenx190::FramelessHelper::QuickWindowBorder>("org.wangwenx190.FramelessHelper", 1);
    qmlRegisterModule("org.wangwenx190.FramelessHelper", 1, 0);
}

static const QQmlModuleRegistration registration("org.wangwenx190.FramelessHelper", qml_register_types_org_wangwenx190_FramelessHelper);
