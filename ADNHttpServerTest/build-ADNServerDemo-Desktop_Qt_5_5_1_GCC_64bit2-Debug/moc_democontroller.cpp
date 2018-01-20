/****************************************************************************
** Meta object code from reading C++ file 'democontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ADNServerDemo/democontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'democontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_demoController_t {
    QByteArrayData data[6];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_demoController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_demoController_t qt_meta_stringdata_demoController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "demoController"
QT_MOC_LITERAL(1, 15, 8), // "getHello"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "params"
QT_MOC_LITERAL(4, 32, 4), // "data"
QT_MOC_LITERAL(5, 37, 8) // "getError"

    },
    "demoController\0getHello\0\0params\0data\0"
    "getError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_demoController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x02 /* Public */,
       5,    2,   29,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,

       0        // eod
};

void demoController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        demoController *_t = static_cast<demoController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QJsonValue _r = _t->getHello((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 1: { QJsonValue _r = _t->getError((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject demoController::staticMetaObject = {
    { &ADNController::staticMetaObject, qt_meta_stringdata_demoController.data,
      qt_meta_data_demoController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *demoController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *demoController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_demoController.stringdata0))
        return static_cast<void*>(const_cast< demoController*>(this));
    return ADNController::qt_metacast(_clname);
}

int demoController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ADNController::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
