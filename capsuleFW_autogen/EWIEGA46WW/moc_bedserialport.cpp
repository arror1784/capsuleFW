/****************************************************************************
** Meta object code from reading C++ file 'bedserialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../bedserialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bedserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BedSerialport_t {
    QByteArrayData data[17];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BedSerialport_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BedSerialport_t qt_meta_stringdata_BedSerialport = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BedSerialport"
QT_MOC_LITERAL(1, 14, 20), // "sendToPrintScheduler"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "bedChar"
QT_MOC_LITERAL(4, 44, 5), // "state"
QT_MOC_LITERAL(5, 50, 3), // "abc"
QT_MOC_LITERAL(6, 54, 15), // "handleReadyRead"
QT_MOC_LITERAL(7, 70, 13), // "handleTimeout"
QT_MOC_LITERAL(8, 84, 11), // "handleError"
QT_MOC_LITERAL(9, 96, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(10, 125, 5), // "error"
QT_MOC_LITERAL(11, 131, 11), // "sendCommand"
QT_MOC_LITERAL(12, 143, 7), // "command"
QT_MOC_LITERAL(13, 151, 15), // "sendByteCommand"
QT_MOC_LITERAL(14, 167, 6), // "buffer"
QT_MOC_LITERAL(15, 174, 9), // "transData"
QT_MOC_LITERAL(16, 184, 15) // "commandFormat_t"

    },
    "BedSerialport\0sendToPrintScheduler\0\0"
    "bedChar\0state\0abc\0handleReadyRead\0"
    "handleTimeout\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "sendCommand\0command\0sendByteCommand\0"
    "buffer\0transData\0commandFormat_t"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BedSerialport[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   60,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    1,   62,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,
      13,    1,   68,    2, 0x0a /* Public */,
      15,    1,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Char, QMetaType::Int,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::QByteArray, 0x80000000 | 16,    2,

       0        // eod
};

void BedSerialport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BedSerialport *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToPrintScheduler((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->abc(); break;
        case 2: _t->handleReadyRead(); break;
        case 3: _t->handleTimeout(); break;
        case 4: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 5: _t->sendCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sendByteCommand((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: { QByteArray _r = _t->transData((*reinterpret_cast< commandFormat_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BedSerialport::*)(char , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BedSerialport::sendToPrintScheduler)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BedSerialport::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BedSerialport::abc)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BedSerialport::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_BedSerialport.data,
    qt_meta_data_BedSerialport,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BedSerialport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BedSerialport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BedSerialport.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BedSerialport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void BedSerialport::sendToPrintScheduler(char _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BedSerialport::abc()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
