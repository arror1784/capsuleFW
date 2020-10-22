/****************************************************************************
** Meta object code from reading C++ file 'wifiinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wifiinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wifiinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WifiInfo_t {
    QByteArrayData data[20];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WifiInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WifiInfo_t qt_meta_stringdata_WifiInfo = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WifiInfo"
QT_MOC_LITERAL(1, 9, 12), // "getNetworkID"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "setNetworkID"
QT_MOC_LITERAL(4, 36, 5), // "value"
QT_MOC_LITERAL(5, 42, 7), // "getSsid"
QT_MOC_LITERAL(6, 50, 7), // "setSsid"
QT_MOC_LITERAL(7, 58, 8), // "getBssid"
QT_MOC_LITERAL(8, 67, 8), // "setBssid"
QT_MOC_LITERAL(9, 76, 8), // "getFlags"
QT_MOC_LITERAL(10, 85, 8), // "setFlags"
QT_MOC_LITERAL(11, 94, 5), // "bool&"
QT_MOC_LITERAL(12, 100, 7), // "getFreq"
QT_MOC_LITERAL(13, 108, 7), // "setFreq"
QT_MOC_LITERAL(14, 116, 15), // "getSignal_level"
QT_MOC_LITERAL(15, 132, 15), // "setSignal_level"
QT_MOC_LITERAL(16, 148, 8), // "getSaved"
QT_MOC_LITERAL(17, 157, 8), // "setSaved"
QT_MOC_LITERAL(18, 166, 12), // "getConnected"
QT_MOC_LITERAL(19, 179, 12) // "setConnected"

    },
    "WifiInfo\0getNetworkID\0\0setNetworkID\0"
    "value\0getSsid\0setSsid\0getBssid\0setBssid\0"
    "getFlags\0setFlags\0bool&\0getFreq\0setFreq\0"
    "getSignal_level\0setSignal_level\0"
    "getSaved\0setSaved\0getConnected\0"
    "setConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WifiInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a /* Public */,
       3,    1,   95,    2, 0x0a /* Public */,
       5,    0,   98,    2, 0x0a /* Public */,
       6,    1,   99,    2, 0x0a /* Public */,
       7,    0,  102,    2, 0x0a /* Public */,
       8,    1,  103,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    1,  107,    2, 0x0a /* Public */,
      12,    0,  110,    2, 0x0a /* Public */,
      13,    1,  111,    2, 0x0a /* Public */,
      14,    0,  114,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x0a /* Public */,
      16,    0,  118,    2, 0x0a /* Public */,
      17,    1,  119,    2, 0x0a /* Public */,
      18,    0,  122,    2, 0x0a /* Public */,
      19,    1,  123,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 11,    4,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void WifiInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WifiInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->getNetworkID();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->setNetworkID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { QString _r = _t->getSsid();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->setSsid((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QString _r = _t->getBssid();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setBssid((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: { bool _r = _t->getFlags();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->setFlags((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: { int _r = _t->getFreq();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setFreq((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { int _r = _t->getSignal_level();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setSignal_level((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: { bool _r = _t->getSaved();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setSaved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: { bool _r = _t->getConnected();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->setConnected((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WifiInfo::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WifiInfo.data,
    qt_meta_data_WifiInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WifiInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WifiInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WifiInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WifiInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
