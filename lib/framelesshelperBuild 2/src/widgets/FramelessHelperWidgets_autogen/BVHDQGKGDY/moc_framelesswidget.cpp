/****************************************************************************
** Meta object code from reading C++ file 'framelesswidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../framelesshelper/include/FramelessHelper/Widgets/framelesswidget.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framelesswidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS = QtMocHelpers::stringData(
    "wangwenx190::FramelessHelper::FramelessWidget",
    "hiddenChanged",
    "",
    "normalChanged",
    "zoomedChanged",
    "toggleMaximized",
    "toggleFullScreen",
    "hidden",
    "normal",
    "zoomed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[46];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[14];
    char stringdata5[16];
    char stringdata6[17];
    char stringdata7[7];
    char stringdata8[7];
    char stringdata9[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS_t qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 45),  // "wangwenx190::FramelessHelper:..."
        QT_MOC_LITERAL(46, 13),  // "hiddenChanged"
        QT_MOC_LITERAL(60, 0),  // ""
        QT_MOC_LITERAL(61, 13),  // "normalChanged"
        QT_MOC_LITERAL(75, 13),  // "zoomedChanged"
        QT_MOC_LITERAL(89, 15),  // "toggleMaximized"
        QT_MOC_LITERAL(105, 16),  // "toggleFullScreen"
        QT_MOC_LITERAL(122, 6),  // "hidden"
        QT_MOC_LITERAL(129, 6),  // "normal"
        QT_MOC_LITERAL(136, 6)   // "zoomed"
    },
    "wangwenx190::FramelessHelper::FramelessWidget",
    "hiddenChanged",
    "",
    "normalChanged",
    "zoomedChanged",
    "toggleMaximized",
    "toggleFullScreen",
    "hidden",
    "normal",
    "zoomed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    4 /* Public */,
       3,    0,   45,    2, 0x06,    5 /* Public */,
       4,    0,   46,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   47,    2, 0x0a,    7 /* Public */,
       6,    0,   48,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Bool, 0x00015801, uint(0), 0,
       8, QMetaType::Bool, 0x00015801, uint(1), 0,
       9, QMetaType::Bool, 0x00015801, uint(2), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject wangwenx190::FramelessHelper::FramelessWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS_t,
        // property 'hidden'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'normal'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'zoomed'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FramelessWidget, std::true_type>,
        // method 'hiddenChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'normalChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'zoomedChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleMaximized'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'toggleFullScreen'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void wangwenx190::FramelessHelper::FramelessWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FramelessWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->hiddenChanged(); break;
        case 1: _t->normalChanged(); break;
        case 2: _t->zoomedChanged(); break;
        case 3: _t->toggleMaximized(); break;
        case 4: _t->toggleFullScreen(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FramelessWidget::*)();
            if (_t _q_method = &FramelessWidget::hiddenChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FramelessWidget::*)();
            if (_t _q_method = &FramelessWidget::normalChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FramelessWidget::*)();
            if (_t _q_method = &FramelessWidget::zoomedChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FramelessWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isHidden(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isNormal(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isZoomed(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *wangwenx190::FramelessHelper::FramelessWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wangwenx190::FramelessHelper::FramelessWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwangwenx190SCOPEFramelessHelperSCOPEFramelessWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int wangwenx190::FramelessHelper::FramelessWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void wangwenx190::FramelessHelper::FramelessWidget::hiddenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void wangwenx190::FramelessHelper::FramelessWidget::normalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void wangwenx190::FramelessHelper::FramelessWidget::zoomedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
