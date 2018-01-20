/****************************************************************************
** Meta object code from reading C++ file 'authcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ADNHttpServer/authcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'authcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_authController_t {
    QByteArrayData data[10];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_authController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_authController_t qt_meta_stringdata_authController = {
    {
QT_MOC_LITERAL(0, 0, 14), // "authController"
QT_MOC_LITERAL(1, 15, 11), // "getValidate"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "params"
QT_MOC_LITERAL(4, 35, 4), // "data"
QT_MOC_LITERAL(5, 40, 13), // "postAuthorize"
QT_MOC_LITERAL(6, 54, 10), // "postRevoke"
QT_MOC_LITERAL(7, 65, 8), // "postDeny"
QT_MOC_LITERAL(8, 74, 11), // "postRequest"
QT_MOC_LITERAL(9, 86, 6) // "getAll"

    },
    "authController\0getValidate\0\0params\0"
    "data\0postAuthorize\0postRevoke\0postDeny\0"
    "postRequest\0getAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_authController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x02 /* Public */,
       5,    2,   49,    2, 0x02 /* Public */,
       6,    2,   54,    2, 0x02 /* Public */,
       7,    2,   59,    2, 0x02 /* Public */,
       8,    2,   64,    2, 0x02 /* Public */,
       9,    2,   69,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,
    QMetaType::QJsonValue, QMetaType::QStringList, QMetaType::QByteArray,    3,    4,

       0        // eod
};

void authController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        authController *_t = static_cast<authController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QJsonValue _r = _t->getValidate((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 1: { QJsonValue _r = _t->postAuthorize((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 2: { QJsonValue _r = _t->postRevoke((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 3: { QJsonValue _r = _t->postDeny((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 4: { QJsonValue _r = _t->postRequest((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        case 5: { QJsonValue _r = _t->getAll((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QJsonValue*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject authController::staticMetaObject = {
    { &ADNController::staticMetaObject, qt_meta_stringdata_authController.data,
      qt_meta_data_authController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *authController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *authController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_authController.stringdata0))
        return static_cast<void*>(const_cast< authController*>(this));
    return ADNController::qt_metacast(_clname);
}

int authController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ADNController::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
