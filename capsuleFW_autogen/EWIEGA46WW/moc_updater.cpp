/****************************************************************************
** Meta object code from reading C++ file 'updater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Updater_t {
    QByteArrayData data[16];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Updater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Updater_t qt_meta_stringdata_Updater = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Updater"
QT_MOC_LITERAL(1, 8, 15), // "updateAvailable"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "updateNotAvailable"
QT_MOC_LITERAL(4, 44, 14), // "updateFinished"
QT_MOC_LITERAL(5, 59, 11), // "updateError"
QT_MOC_LITERAL(6, 71, 17), // "updateMCUFirmware"
QT_MOC_LITERAL(7, 89, 4), // "path"
QT_MOC_LITERAL(8, 94, 7), // "version"
QT_MOC_LITERAL(9, 102, 14), // "lastestVersion"
QT_MOC_LITERAL(10, 117, 15), // "requestFinished"
QT_MOC_LITERAL(11, 133, 14), // "QNetworkReply*"
QT_MOC_LITERAL(12, 148, 5), // "reply"
QT_MOC_LITERAL(13, 154, 25), // "MCUFirmwareUpdateFinished"
QT_MOC_LITERAL(14, 180, 11), // "checkUpdate"
QT_MOC_LITERAL(15, 192, 6) // "update"

    },
    "Updater\0updateAvailable\0\0updateNotAvailable\0"
    "updateFinished\0updateError\0updateMCUFirmware\0"
    "path\0version\0lastestVersion\0requestFinished\0"
    "QNetworkReply*\0reply\0MCUFirmwareUpdateFinished\0"
    "checkUpdate\0update"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Updater[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    1,   78,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    0,   82,    2, 0x0a /* Public */,
      15,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Updater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Updater *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateAvailable(); break;
        case 1: _t->updateNotAvailable(); break;
        case 2: _t->updateFinished(); break;
        case 3: _t->updateError(); break;
        case 4: _t->updateMCUFirmware((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { QString _r = _t->version();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { QString _r = _t->lastestVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->MCUFirmwareUpdateFinished(); break;
        case 9: _t->checkUpdate(); break;
        case 10: _t->update(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Updater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::updateAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Updater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::updateNotAvailable)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Updater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::updateFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Updater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::updateError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Updater::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::updateMCUFirmware)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Updater::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Updater.data,
    qt_meta_data_Updater,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Updater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Updater::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Updater.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Updater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Updater::updateAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Updater::updateNotAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Updater::updateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Updater::updateError()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Updater::updateMCUFirmware(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
