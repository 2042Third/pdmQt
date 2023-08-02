/****************************************************************************
** Meta object code from reading C++ file 'windowborderpainter_p.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../framelesshelper/include/FramelessHelper/Core/private/windowborderpainter_p.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowborderpainter_p.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS = QtMocHelpers::stringData(
    "wangwenx190::FramelessHelper::WindowBorderPainterPrivate",
    "paint",
    "",
    "QPainter*",
    "painter",
    "size",
    "active"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[57];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[8];
    char stringdata5[5];
    char stringdata6[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS_t qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS = {
    {
        QT_MOC_LITERAL(0, 56),  // "wangwenx190::FramelessHelper:..."
        QT_MOC_LITERAL(57, 5),  // "paint"
        QT_MOC_LITERAL(63, 0),  // ""
        QT_MOC_LITERAL(64, 9),  // "QPainter*"
        QT_MOC_LITERAL(74, 7),  // "painter"
        QT_MOC_LITERAL(82, 4),  // "size"
        QT_MOC_LITERAL(87, 6)   // "active"
    },
    "wangwenx190::FramelessHelper::WindowBorderPainterPrivate",
    "paint",
    "",
    "QPainter*",
    "painter",
    "size",
    "active"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   20,    2, 0x10a,    1 /* Public | MethodIsConst  */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QSize, QMetaType::Bool,    4,    5,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject wangwenx190::FramelessHelper::WindowBorderPainterPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WindowBorderPainterPrivate, std::true_type>,
        // method 'paint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPainter *, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSize &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const bool, std::false_type>
    >,
    nullptr
} };

void wangwenx190::FramelessHelper::WindowBorderPainterPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowBorderPainterPrivate *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->paint((*reinterpret_cast< std::add_pointer_t<QPainter*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QSize>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject *wangwenx190::FramelessHelper::WindowBorderPainterPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wangwenx190::FramelessHelper::WindowBorderPainterPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEWindowBorderPainterPrivateENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int wangwenx190::FramelessHelper::WindowBorderPainterPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
