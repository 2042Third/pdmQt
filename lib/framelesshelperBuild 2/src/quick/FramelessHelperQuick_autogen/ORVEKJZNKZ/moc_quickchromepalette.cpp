/****************************************************************************
** Meta object code from reading C++ file 'quickchromepalette.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../framelesshelper/include/FramelessHelper/Quick/quickchromepalette.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quickchromepalette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS = QtMocHelpers::stringData(
    "wangwenx190::FramelessHelper::QuickChromePalette",
    "QML.Element",
    "anonymous"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS_t {
    uint offsetsAndSizes[6];
    char stringdata0[49];
    char stringdata1[12];
    char stringdata2[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS_t qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS = {
    {
        QT_MOC_LITERAL(0, 48),  // "wangwenx190::FramelessHelper:..."
        QT_MOC_LITERAL(49, 11),  // "QML.Element"
        QT_MOC_LITERAL(61, 9)   // "anonymous"
    },
    "wangwenx190::FramelessHelper::QuickChromePalette",
    "QML.Element",
    "anonymous"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       1,   14, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject wangwenx190::FramelessHelper::QuickChromePalette::staticMetaObject = { {
    QMetaObject::SuperData::link<ChromePalette::staticMetaObject>(),
    qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // Q_OBJECT / Q_GADGET
        QuickChromePalette
    >,
    nullptr
} };

void wangwenx190::FramelessHelper::QuickChromePalette::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *wangwenx190::FramelessHelper::QuickChromePalette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wangwenx190::FramelessHelper::QuickChromePalette::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEQuickChromePaletteENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QQmlParserStatus"))
        return static_cast< QQmlParserStatus*>(this);
    return ChromePalette::qt_metacast(_clname);
}

int wangwenx190::FramelessHelper::QuickChromePalette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChromePalette::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
