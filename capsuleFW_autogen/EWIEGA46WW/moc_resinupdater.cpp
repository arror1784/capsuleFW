/****************************************************************************
** Meta object code from reading C++ file 'resinupdater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../resinupdater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resinupdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ResinUpdater_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ResinUpdater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ResinUpdater_t qt_meta_stringdata_ResinUpdater = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ResinUpdater"
QT_MOC_LITERAL(1, 13, 15), // "updateAvailable"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "updateNotAvailable"
QT_MOC_LITERAL(4, 49, 14), // "updateFinished"
QT_MOC_LITERAL(5, 64, 11), // "updateError"
QT_MOC_LITERAL(6, 76, 15), // "requestFinished"
QT_MOC_LITERAL(7, 92, 14), // "QNetworkReply*"
QT_MOC_LITERAL(8, 107, 5), // "reply"
QT_MOC_LITERAL(9, 113, 11), // "checkUpdate"
QT_MOC_LITERAL(10, 125, 6), // "update"
QT_MOC_LITERAL(11, 132, 7), // "version"
QT_MOC_LITERAL(12, 140, 14) // "lastestVersion"

    },
    "ResinUpdater\0updateAvailable\0\0"
    "updateNotAvailable\0updateFinished\0"
    "updateError\0requestFinished\0QNetworkReply*\0"
    "reply\0checkUpdate\0update\0version\0"
    "lastestVersion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ResinUpdater[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   63,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,
      11,    0,   68,    2, 0x0a /* Public */,
      12,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,

       0        // eod
};

void ResinUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ResinUpdater *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateAvailable(); break;
        case 1: _t->updateNotAvailable(); break;
        case 2: _t->updateFinished(); break;
        case 3: _t->updateError(); break;
        case 4: _t->requestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->checkUpdate(); break;
        case 6: _t->update(); break;
        case 7: { QString _r = _t->version();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { QString _r = _t->lastestVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ResinUpdater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResinUpdater::updateAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ResinUpdater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResinUpdater::updateNotAvailable)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ResinUpdater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResinUpdater::updateFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ResinUpdater::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ResinUpdater::updateError)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ResinUpdater::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ResinUpdater.data,
    qt_meta_data_ResinUpdater,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ResinUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ResinUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ResinUpdater.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ResinUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ResinUpdater::updateAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ResinUpdater::updateNotAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ResinUpdater::updateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ResinUpdater::updateError()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
