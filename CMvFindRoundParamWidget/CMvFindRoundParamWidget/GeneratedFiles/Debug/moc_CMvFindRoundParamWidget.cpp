/****************************************************************************
** Meta object code from reading C++ file 'CMvFindRoundParamWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CMvFindRoundParamWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMvFindRoundParamWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CMvFindRoundParamWidget_t {
    QByteArrayData data[8];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CMvFindRoundParamWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CMvFindRoundParamWidget_t qt_meta_stringdata_CMvFindRoundParamWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "CMvFindRoundParamWidget"
QT_MOC_LITERAL(1, 24, 24), // "slotGetDetectorNameValue"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 26), // "slotGetEnableDetectorValue"
QT_MOC_LITERAL(4, 77, 5), // "state"
QT_MOC_LITERAL(5, 83, 22), // "slotGetROISourcesValue"
QT_MOC_LITERAL(6, 106, 5), // "index"
QT_MOC_LITERAL(7, 112, 26) // "slotGetCreateYourselfValue"

    },
    "CMvFindRoundParamWidget\0"
    "slotGetDetectorNameValue\0\0"
    "slotGetEnableDetectorValue\0state\0"
    "slotGetROISourcesValue\0index\0"
    "slotGetCreateYourselfValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CMvFindRoundParamWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       5,    1,   38,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void CMvFindRoundParamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CMvFindRoundParamWidget *_t = static_cast<CMvFindRoundParamWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotGetDetectorNameValue(); break;
        case 1: _t->slotGetEnableDetectorValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotGetROISourcesValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotGetCreateYourselfValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CMvFindRoundParamWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CMvFindRoundParamWidget.data,
      qt_meta_data_CMvFindRoundParamWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CMvFindRoundParamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CMvFindRoundParamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CMvFindRoundParamWidget.stringdata0))
        return static_cast<void*>(const_cast< CMvFindRoundParamWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CMvFindRoundParamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
