/****************************************************************************
** Meta object code from reading C++ file 'framelessmainwindow_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../framelesshelper/include/FramelessHelper/Widgets/private/framelessmainwindow_p.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framelessmainwindow_p.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS = QtMocHelpers::stringData(
    "wangwenx190::FramelessHelper::FramelessMainWindowPrivate"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS_t {
    uint offsetsAndSizes[2];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS_t qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS = {
    {
        QT_MOC_LITERAL(0, 56)   // "wangwenx190::FramelessHelper:..."
    },
    "wangwenx190::FramelessHelper::FramelessMainWindowPrivate"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject wangwenx190::FramelessHelper::FramelessMainWindowPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FramelessMainWindowPrivate, std::true_type>
    >,
    nullptr
} };

void wangwenx190::FramelessHelper::FramelessMainWindowPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *wangwenx190::FramelessHelper::FramelessMainWindowPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wangwenx190::FramelessHelper::FramelessMainWindowPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessMainWindowPrivateENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int wangwenx190::FramelessHelper::FramelessMainWindowPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
