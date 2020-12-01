/****************************************************************************
** Meta object code from reading C++ file 'CMvBlackAndWhiteConversionColor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/CMvBlackAndWhiteConversionColor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMvBlackAndWhiteConversionColor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMvBlackAndWhiteConversionColor_t {
    QByteArrayData data[16];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMvBlackAndWhiteConversionColor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMvBlackAndWhiteConversionColor_t qt_meta_stringdata_CMvBlackAndWhiteConversionColor = {
    {
QT_MOC_LITERAL(0, 0, 31), // "CMvBlackAndWhiteConversionColor"
QT_MOC_LITERAL(1, 32, 19), // "slotClickPushButton"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 3), // "row"
QT_MOC_LITERAL(4, 57, 3), // "col"
QT_MOC_LITERAL(5, 61, 17), // "soltMenuTriggered"
QT_MOC_LITERAL(6, 79, 8), // "QAction*"
QT_MOC_LITERAL(7, 88, 6), // "action"
QT_MOC_LITERAL(8, 95, 26), // "slotGetStartUpDrawingValue"
QT_MOC_LITERAL(9, 122, 5), // "State"
QT_MOC_LITERAL(10, 128, 15), // "slotOnceIsClick"
QT_MOC_LITERAL(11, 144, 19), // "slotMakeSureIsClick"
QT_MOC_LITERAL(12, 164, 17), // "slotCancelIsClick"
QT_MOC_LITERAL(13, 182, 24), // "slotGetDetectorNameValue"
QT_MOC_LITERAL(14, 207, 26), // "slotGetEnableDetectorValue"
QT_MOC_LITERAL(15, 234, 5) // "state"

    },
    "CMvBlackAndWhiteConversionColor\0"
    "slotClickPushButton\0\0row\0col\0"
    "soltMenuTriggered\0QAction*\0action\0"
    "slotGetStartUpDrawingValue\0State\0"
    "slotOnceIsClick\0slotMakeSureIsClick\0"
    "slotCancelIsClick\0slotGetDetectorNameValue\0"
    "slotGetEnableDetectorValue\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMvBlackAndWhiteConversionColor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x08 /* Private */,
       5,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,
      13,    0,   68,    2, 0x08 /* Private */,
      14,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void CMvBlackAndWhiteConversionColor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMvBlackAndWhiteConversionColor *_t = static_cast<CMvBlackAndWhiteConversionColor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotClickPushButton((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->soltMenuTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->slotGetStartUpDrawingValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->slotOnceIsClick(); break;
        case 4: _t->slotMakeSureIsClick(); break;
        case 5: _t->slotCancelIsClick(); break;
        case 6: _t->slotGetDetectorNameValue(); break;
        case 7: _t->slotGetEnableDetectorValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject CMvBlackAndWhiteConversionColor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CMvBlackAndWhiteConversionColor.data,
      qt_meta_data_CMvBlackAndWhiteConversionColor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMvBlackAndWhiteConversionColor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMvBlackAndWhiteConversionColor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMvBlackAndWhiteConversionColor.stringdata0))
        return static_cast<void*>(const_cast< CMvBlackAndWhiteConversionColor*>(this));
    return QWidget::qt_metacast(_clname);
}

int CMvBlackAndWhiteConversionColor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
