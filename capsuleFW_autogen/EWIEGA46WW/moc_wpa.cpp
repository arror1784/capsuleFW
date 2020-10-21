/****************************************************************************
** Meta object code from reading C++ file 'wpa.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wpa.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wpa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WPA_t {
    QByteArrayData data[22];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WPA_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WPA_t qt_meta_stringdata_WPA = {
    {
QT_MOC_LITERAL(0, 0, 3), // "WPA"
QT_MOC_LITERAL(1, 4, 17), // "networkListUpdate"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 18), // "currentStateChange"
QT_MOC_LITERAL(4, 42, 15), // "connectedChange"
QT_MOC_LITERAL(5, 58, 9), // "connected"
QT_MOC_LITERAL(6, 68, 16), // "refreshAvailable"
QT_MOC_LITERAL(7, 85, 11), // "networkScan"
QT_MOC_LITERAL(8, 97, 12), // "networkCount"
QT_MOC_LITERAL(9, 110, 10), // "getNetwork"
QT_MOC_LITERAL(10, 121, 9), // "WifiInfo*"
QT_MOC_LITERAL(11, 131, 5), // "index"
QT_MOC_LITERAL(12, 137, 14), // "networkConnect"
QT_MOC_LITERAL(13, 152, 4), // "ssid"
QT_MOC_LITERAL(14, 157, 5), // "bssid"
QT_MOC_LITERAL(15, 163, 6), // "passwd"
QT_MOC_LITERAL(16, 170, 9), // "networkID"
QT_MOC_LITERAL(17, 180, 2), // "id"
QT_MOC_LITERAL(18, 183, 17), // "networkDisconnect"
QT_MOC_LITERAL(19, 201, 13), // "networkDelete"
QT_MOC_LITERAL(20, 215, 19), // "checkNetworkConnect"
QT_MOC_LITERAL(21, 235, 11) // "currentSSID"

    },
    "WPA\0networkListUpdate\0\0currentStateChange\0"
    "connectedChange\0connected\0refreshAvailable\0"
    "networkScan\0networkCount\0getNetwork\0"
    "WifiInfo*\0index\0networkConnect\0ssid\0"
    "bssid\0passwd\0networkID\0id\0networkDisconnect\0"
    "networkDelete\0checkNetworkConnect\0"
    "currentSSID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WPA[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    1,  101,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  105,    2, 0x0a /* Public */,
       8,    0,  106,    2, 0x0a /* Public */,
       9,    1,  107,    2, 0x0a /* Public */,
      12,    4,  110,    2, 0x0a /* Public */,
      12,    3,  119,    2, 0x0a /* Public */,
      12,    1,  126,    2, 0x0a /* Public */,
      12,    3,  129,    2, 0x0a /* Public */,
      12,    2,  136,    2, 0x0a /* Public */,
      18,    0,  141,    2, 0x0a /* Public */,
      19,    1,  142,    2, 0x0a /* Public */,
      19,    1,  145,    2, 0x0a /* Public */,
      20,    0,  148,    2, 0x0a /* Public */,
      21,    0,  149,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Int,
    0x80000000 | 10, QMetaType::Int,   11,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   13,   14,   15,   16,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,   13,   14,   15,
    QMetaType::Bool, QMetaType::Int,   17,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,   13,   14,   16,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,   13,   14,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

void WPA::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WPA *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->networkListUpdate(); break;
        case 1: _t->currentStateChange(); break;
        case 2: _t->connectedChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->refreshAvailable(); break;
        case 4: _t->networkScan(); break;
        case 5: { int _r = _t->networkCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { WifiInfo* _r = _t->getNetwork((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< WifiInfo**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->networkConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->networkConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->networkConnect((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->networkConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: { bool _r = _t->networkConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: { bool _r = _t->networkDisconnect();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->networkDelete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->networkDelete((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->checkNetworkConnect(); break;
        case 16: { QString _r = _t->currentSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WPA::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WPA::networkListUpdate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WPA::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WPA::currentStateChange)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WPA::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WPA::connectedChange)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WPA::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WPA::refreshAvailable)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WPA::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WPA.data,
    qt_meta_data_WPA,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WPA::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WPA::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WPA.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WPA::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void WPA::networkListUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WPA::currentStateChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WPA::connectedChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WPA::refreshAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
