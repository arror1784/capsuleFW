/****************************************************************************
** Meta object code from reading C++ file 'qmlconnecter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qmlconnecter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmlconnecter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QmlConnecter_t {
    QByteArrayData data[90];
    char stringdata0[1635];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlConnecter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QmlConnecter_t qt_meta_stringdata_QmlConnecter = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QmlConnecter"
QT_MOC_LITERAL(1, 13, 19), // "sendTOQMLPrintStart"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "path"
QT_MOC_LITERAL(4, 39, 12), // "materialName"
QT_MOC_LITERAL(5, 52, 21), // "sendToSchedPrintStart"
QT_MOC_LITERAL(6, 74, 8), // "fileName"
QT_MOC_LITERAL(7, 83, 4), // "byte"
QT_MOC_LITERAL(8, 88, 21), // "sendToSchedPrintAgain"
QT_MOC_LITERAL(9, 110, 22), // "sendToSchedPrintResume"
QT_MOC_LITERAL(10, 133, 21), // "sendToSchedPrintPause"
QT_MOC_LITERAL(11, 155, 22), // "sendToSchedPrintFinish"
QT_MOC_LITERAL(12, 178, 26), // "sendToSchedGetMaterialList"
QT_MOC_LITERAL(13, 205, 28), // "sendToSchedGetPrintInfoToWeb"
QT_MOC_LITERAL(14, 234, 26), // "sendToSchedGetHeightOffset"
QT_MOC_LITERAL(15, 261, 23), // "sendToSchedGetLedOffset"
QT_MOC_LITERAL(16, 285, 28), // "sendToSchedGetMaterialOption"
QT_MOC_LITERAL(17, 314, 8), // "material"
QT_MOC_LITERAL(18, 323, 25), // "sendToSchedGetPrintOption"
QT_MOC_LITERAL(19, 349, 25), // "sendToSchedGetInfoSetting"
QT_MOC_LITERAL(20, 375, 28), // "sendToSchedSetTotalPrintTime"
QT_MOC_LITERAL(21, 404, 4), // "time"
QT_MOC_LITERAL(22, 409, 27), // "sendToSchedPrintFinishError"
QT_MOC_LITERAL(23, 437, 26), // "sendToSchedSetHeightOffset"
QT_MOC_LITERAL(24, 464, 5), // "value"
QT_MOC_LITERAL(25, 470, 23), // "sendToSchedSetLedOffset"
QT_MOC_LITERAL(26, 494, 8), // "isCustom"
QT_MOC_LITERAL(27, 503, 18), // "sendToSchedBusySet"
QT_MOC_LITERAL(28, 522, 2), // "bs"
QT_MOC_LITERAL(29, 525, 19), // "sendToSchedShutdown"
QT_MOC_LITERAL(30, 545, 17), // "sendToSchedGoHome"
QT_MOC_LITERAL(31, 563, 19), // "sendToSchedAutoHome"
QT_MOC_LITERAL(32, 583, 20), // "sendToSchedMoveMicro"
QT_MOC_LITERAL(33, 604, 5), // "micro"
QT_MOC_LITERAL(34, 610, 24), // "sendToSchedMoveMaxHeight"
QT_MOC_LITERAL(35, 635, 21), // "sendToSchedGetVersion"
QT_MOC_LITERAL(36, 657, 21), // "sendToSchedGetModelNo"
QT_MOC_LITERAL(37, 679, 23), // "sendToSchedSetPrintTime"
QT_MOC_LITERAL(38, 703, 28), // "receiveFromUpdaterFirmUpdate"
QT_MOC_LITERAL(39, 732, 18), // "receiveChangeImage"
QT_MOC_LITERAL(40, 751, 9), // "imagePath"
QT_MOC_LITERAL(41, 761, 20), // "receiveSetImageScale"
QT_MOC_LITERAL(42, 782, 21), // "receiveUpdateProgress"
QT_MOC_LITERAL(43, 804, 8), // "progress"
QT_MOC_LITERAL(44, 813, 22), // "receiveFirstlayerStart"
QT_MOC_LITERAL(45, 836, 23), // "receiveFirstlayerFinish"
QT_MOC_LITERAL(46, 860, 20), // "receiveChangeToPrint"
QT_MOC_LITERAL(47, 881, 25), // "receiveChangeToPauseStart"
QT_MOC_LITERAL(48, 907, 26), // "receiveChangeToPauseFinish"
QT_MOC_LITERAL(49, 934, 21), // "receiveChangeToResume"
QT_MOC_LITERAL(50, 956, 19), // "receiveChangeToQuit"
QT_MOC_LITERAL(51, 976, 26), // "receiveChangeToPrintFinish"
QT_MOC_LITERAL(52, 1003, 29), // "receiveChangeToPrintWorkError"
QT_MOC_LITERAL(53, 1033, 35), // "receiveChangeToPrintWorkError..."
QT_MOC_LITERAL(54, 1069, 24), // "receivePrintSettingError"
QT_MOC_LITERAL(55, 1094, 4), // "code"
QT_MOC_LITERAL(56, 1099, 18), // "receiveEnableTimer"
QT_MOC_LITERAL(57, 1118, 6), // "enable"
QT_MOC_LITERAL(58, 1125, 19), // "receiveMaterialList"
QT_MOC_LITERAL(59, 1145, 4), // "name"
QT_MOC_LITERAL(60, 1150, 16), // "receivePrintInfo"
QT_MOC_LITERAL(61, 1167, 12), // "printerState"
QT_MOC_LITERAL(62, 1180, 11), // "layerHeight"
QT_MOC_LITERAL(63, 1192, 11), // "elapsedTime"
QT_MOC_LITERAL(64, 1204, 9), // "totalTime"
QT_MOC_LITERAL(65, 1214, 11), // "enableTimer"
QT_MOC_LITERAL(66, 1226, 19), // "receiveSetTotalTime"
QT_MOC_LITERAL(67, 1246, 20), // "receivePortOpenError"
QT_MOC_LITERAL(68, 1267, 15), // "receiveLCDState"
QT_MOC_LITERAL(69, 1283, 5), // "state"
QT_MOC_LITERAL(70, 1289, 16), // "receiveExitError"
QT_MOC_LITERAL(71, 1306, 11), // "receiveExit"
QT_MOC_LITERAL(72, 1318, 13), // "receiveMoveOk"
QT_MOC_LITERAL(73, 1332, 25), // "MCUFirmwareUpdateFinished"
QT_MOC_LITERAL(74, 1358, 24), // "receiveSWUpdateAvailable"
QT_MOC_LITERAL(75, 1383, 27), // "receiveSWUpdateNotAvailable"
QT_MOC_LITERAL(76, 1411, 23), // "receiveSWUpdateFinished"
QT_MOC_LITERAL(77, 1435, 20), // "receiveSWUpdateError"
QT_MOC_LITERAL(78, 1456, 19), // "receiveHeightOffset"
QT_MOC_LITERAL(79, 1476, 6), // "offset"
QT_MOC_LITERAL(80, 1483, 16), // "receiveLEDOffset"
QT_MOC_LITERAL(81, 1500, 21), // "receiveMaterialOption"
QT_MOC_LITERAL(82, 1522, 6), // "option"
QT_MOC_LITERAL(83, 1529, 21), // "receiveGetPrintOption"
QT_MOC_LITERAL(84, 1551, 21), // "receiveGetInfoSetting"
QT_MOC_LITERAL(85, 1573, 15), // "receiveIsCustom"
QT_MOC_LITERAL(86, 1589, 14), // "receiveVersion"
QT_MOC_LITERAL(87, 1604, 7), // "version"
QT_MOC_LITERAL(88, 1612, 14), // "receiveModelNo"
QT_MOC_LITERAL(89, 1627, 7) // "modelNo"

    },
    "QmlConnecter\0sendTOQMLPrintStart\0\0"
    "path\0materialName\0sendToSchedPrintStart\0"
    "fileName\0byte\0sendToSchedPrintAgain\0"
    "sendToSchedPrintResume\0sendToSchedPrintPause\0"
    "sendToSchedPrintFinish\0"
    "sendToSchedGetMaterialList\0"
    "sendToSchedGetPrintInfoToWeb\0"
    "sendToSchedGetHeightOffset\0"
    "sendToSchedGetLedOffset\0"
    "sendToSchedGetMaterialOption\0material\0"
    "sendToSchedGetPrintOption\0"
    "sendToSchedGetInfoSetting\0"
    "sendToSchedSetTotalPrintTime\0time\0"
    "sendToSchedPrintFinishError\0"
    "sendToSchedSetHeightOffset\0value\0"
    "sendToSchedSetLedOffset\0isCustom\0"
    "sendToSchedBusySet\0bs\0sendToSchedShutdown\0"
    "sendToSchedGoHome\0sendToSchedAutoHome\0"
    "sendToSchedMoveMicro\0micro\0"
    "sendToSchedMoveMaxHeight\0sendToSchedGetVersion\0"
    "sendToSchedGetModelNo\0sendToSchedSetPrintTime\0"
    "receiveFromUpdaterFirmUpdate\0"
    "receiveChangeImage\0imagePath\0"
    "receiveSetImageScale\0receiveUpdateProgress\0"
    "progress\0receiveFirstlayerStart\0"
    "receiveFirstlayerFinish\0receiveChangeToPrint\0"
    "receiveChangeToPauseStart\0"
    "receiveChangeToPauseFinish\0"
    "receiveChangeToResume\0receiveChangeToQuit\0"
    "receiveChangeToPrintFinish\0"
    "receiveChangeToPrintWorkError\0"
    "receiveChangeToPrintWorkErrorFinish\0"
    "receivePrintSettingError\0code\0"
    "receiveEnableTimer\0enable\0receiveMaterialList\0"
    "name\0receivePrintInfo\0printerState\0"
    "layerHeight\0elapsedTime\0totalTime\0"
    "enableTimer\0receiveSetTotalTime\0"
    "receivePortOpenError\0receiveLCDState\0"
    "state\0receiveExitError\0receiveExit\0"
    "receiveMoveOk\0MCUFirmwareUpdateFinished\0"
    "receiveSWUpdateAvailable\0"
    "receiveSWUpdateNotAvailable\0"
    "receiveSWUpdateFinished\0receiveSWUpdateError\0"
    "receiveHeightOffset\0offset\0receiveLEDOffset\0"
    "receiveMaterialOption\0option\0"
    "receiveGetPrintOption\0receiveGetInfoSetting\0"
    "receiveIsCustom\0receiveVersion\0version\0"
    "receiveModelNo\0modelNo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlConnecter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      64,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      28,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  334,    2, 0x06 /* Public */,
       5,    3,  339,    2, 0x06 /* Public */,
       8,    0,  346,    2, 0x06 /* Public */,
       9,    0,  347,    2, 0x06 /* Public */,
      10,    0,  348,    2, 0x06 /* Public */,
      11,    0,  349,    2, 0x06 /* Public */,
      12,    0,  350,    2, 0x06 /* Public */,
      13,    0,  351,    2, 0x06 /* Public */,
      14,    0,  352,    2, 0x06 /* Public */,
      15,    0,  353,    2, 0x06 /* Public */,
      16,    1,  354,    2, 0x06 /* Public */,
      18,    0,  357,    2, 0x06 /* Public */,
      19,    1,  358,    2, 0x06 /* Public */,
      20,    1,  361,    2, 0x06 /* Public */,
      22,    0,  364,    2, 0x06 /* Public */,
      23,    1,  365,    2, 0x06 /* Public */,
      25,    1,  368,    2, 0x06 /* Public */,
      26,    1,  371,    2, 0x06 /* Public */,
      27,    1,  374,    2, 0x06 /* Public */,
      29,    0,  377,    2, 0x06 /* Public */,
      30,    0,  378,    2, 0x06 /* Public */,
      31,    0,  379,    2, 0x06 /* Public */,
      32,    1,  380,    2, 0x06 /* Public */,
      34,    0,  383,    2, 0x06 /* Public */,
      35,    0,  384,    2, 0x06 /* Public */,
      36,    0,  385,    2, 0x06 /* Public */,
      37,    1,  386,    2, 0x06 /* Public */,
      38,    1,  389,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      39,    1,  392,    2, 0x0a /* Public */,
      41,    1,  395,    2, 0x0a /* Public */,
      42,    1,  398,    2, 0x0a /* Public */,
      44,    0,  401,    2, 0x0a /* Public */,
      45,    0,  402,    2, 0x0a /* Public */,
      46,    0,  403,    2, 0x0a /* Public */,
      47,    0,  404,    2, 0x0a /* Public */,
      48,    0,  405,    2, 0x0a /* Public */,
      49,    0,  406,    2, 0x0a /* Public */,
      50,    0,  407,    2, 0x0a /* Public */,
      51,    0,  408,    2, 0x0a /* Public */,
      52,    0,  409,    2, 0x0a /* Public */,
      53,    0,  410,    2, 0x0a /* Public */,
      54,    1,  411,    2, 0x0a /* Public */,
      56,    1,  414,    2, 0x0a /* Public */,
      58,    1,  417,    2, 0x0a /* Public */,
      60,    8,  420,    2, 0x0a /* Public */,
      66,    1,  437,    2, 0x0a /* Public */,
      67,    0,  440,    2, 0x0a /* Public */,
      68,    1,  441,    2, 0x0a /* Public */,
      70,    0,  444,    2, 0x0a /* Public */,
      71,    0,  445,    2, 0x0a /* Public */,
      72,    0,  446,    2, 0x0a /* Public */,
      73,    0,  447,    2, 0x0a /* Public */,
      74,    0,  448,    2, 0x0a /* Public */,
      75,    0,  449,    2, 0x0a /* Public */,
      76,    0,  450,    2, 0x0a /* Public */,
      77,    0,  451,    2, 0x0a /* Public */,
      78,    1,  452,    2, 0x0a /* Public */,
      80,    1,  455,    2, 0x0a /* Public */,
      81,    2,  458,    2, 0x0a /* Public */,
      83,    1,  463,    2, 0x0a /* Public */,
      84,    2,  466,    2, 0x0a /* Public */,
      85,    1,  471,    2, 0x0a /* Public */,
      86,    1,  474,    2, 0x0a /* Public */,
      88,    1,  477,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QJsonObject,    6,    4,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Double,
    QMetaType::QString, QMetaType::QString,   17,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Bool, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Bool,   57,
    QMetaType::Void, QMetaType::QVariantList,   59,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   61,   17,    6,   62,   63,   64,   43,   65,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   69,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   79,
    QMetaType::Void, QMetaType::Double,   79,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   17,   82,
    QMetaType::Void, QMetaType::QString,   82,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,   82,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::QString,   87,
    QMetaType::Void, QMetaType::QString,   89,

       0        // eod
};

void QmlConnecter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QmlConnecter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendTOQMLPrintStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sendToSchedPrintStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 2: _t->sendToSchedPrintAgain(); break;
        case 3: _t->sendToSchedPrintResume(); break;
        case 4: _t->sendToSchedPrintPause(); break;
        case 5: _t->sendToSchedPrintFinish(); break;
        case 6: _t->sendToSchedGetMaterialList(); break;
        case 7: _t->sendToSchedGetPrintInfoToWeb(); break;
        case 8: { int _r = _t->sendToSchedGetHeightOffset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { double _r = _t->sendToSchedGetLedOffset();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 10: { QString _r = _t->sendToSchedGetMaterialOption((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: { QString _r = _t->sendToSchedGetPrintOption();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: { QString _r = _t->sendToSchedGetInfoSetting((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->sendToSchedSetTotalPrintTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->sendToSchedPrintFinishError(); break;
        case 15: _t->sendToSchedSetHeightOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->sendToSchedSetLedOffset((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: { bool _r = _t->isCustom((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->sendToSchedBusySet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->sendToSchedShutdown(); break;
        case 20: _t->sendToSchedGoHome(); break;
        case 21: _t->sendToSchedAutoHome(); break;
        case 22: _t->sendToSchedMoveMicro((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->sendToSchedMoveMaxHeight(); break;
        case 24: _t->sendToSchedGetVersion(); break;
        case 25: _t->sendToSchedGetModelNo(); break;
        case 26: _t->sendToSchedSetPrintTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->receiveFromUpdaterFirmUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 28: _t->receiveChangeImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->receiveSetImageScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->receiveUpdateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->receiveFirstlayerStart(); break;
        case 32: _t->receiveFirstlayerFinish(); break;
        case 33: _t->receiveChangeToPrint(); break;
        case 34: _t->receiveChangeToPauseStart(); break;
        case 35: _t->receiveChangeToPauseFinish(); break;
        case 36: _t->receiveChangeToResume(); break;
        case 37: _t->receiveChangeToQuit(); break;
        case 38: _t->receiveChangeToPrintFinish(); break;
        case 39: _t->receiveChangeToPrintWorkError(); break;
        case 40: _t->receiveChangeToPrintWorkErrorFinish(); break;
        case 41: _t->receivePrintSettingError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->receiveEnableTimer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->receiveMaterialList((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 44: _t->receivePrintInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< bool(*)>(_a[8]))); break;
        case 45: _t->receiveSetTotalTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: _t->receivePortOpenError(); break;
        case 47: _t->receiveLCDState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 48: _t->receiveExitError(); break;
        case 49: _t->receiveExit(); break;
        case 50: _t->receiveMoveOk(); break;
        case 51: _t->MCUFirmwareUpdateFinished(); break;
        case 52: _t->receiveSWUpdateAvailable(); break;
        case 53: _t->receiveSWUpdateNotAvailable(); break;
        case 54: _t->receiveSWUpdateFinished(); break;
        case 55: _t->receiveSWUpdateError(); break;
        case 56: _t->receiveHeightOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: _t->receiveLEDOffset((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 58: _t->receiveMaterialOption((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 59: _t->receiveGetPrintOption((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 60: _t->receiveGetInfoSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 61: _t->receiveIsCustom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->receiveVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 63: _t->receiveModelNo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QmlConnecter::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendTOQMLPrintStart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(QString , QString , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintStart)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintAgain)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintResume)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintPause)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintFinish)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetMaterialList)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetPrintInfoToWeb)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = int (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetHeightOffset)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = double (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetLedOffset)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = QString (QmlConnecter::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetMaterialOption)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = QString (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetPrintOption)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = QString (QmlConnecter::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetInfoSetting)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedSetTotalPrintTime)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedPrintFinishError)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedSetHeightOffset)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedSetLedOffset)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = bool (QmlConnecter::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::isCustom)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedBusySet)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedShutdown)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGoHome)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedAutoHome)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedMoveMicro)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedMoveMaxHeight)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetVersion)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedGetModelNo)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::sendToSchedSetPrintTime)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (QmlConnecter::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QmlConnecter::receiveFromUpdaterFirmUpdate)) {
                *result = 27;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QmlConnecter::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QmlConnecter.data,
    qt_meta_data_QmlConnecter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QmlConnecter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QmlConnecter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QmlConnecter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QmlConnecter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 64)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 64;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 64)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 64;
    }
    return _id;
}

// SIGNAL 0
void QmlConnecter::sendTOQMLPrintStart(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QmlConnecter::sendToSchedPrintStart(QString _t1, QString _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QmlConnecter::sendToSchedPrintAgain()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QmlConnecter::sendToSchedPrintResume()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QmlConnecter::sendToSchedPrintPause()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void QmlConnecter::sendToSchedPrintFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QmlConnecter::sendToSchedGetMaterialList()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void QmlConnecter::sendToSchedGetPrintInfoToWeb()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
int QmlConnecter::sendToSchedGetHeightOffset()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
    return _t0;
}

// SIGNAL 9
double QmlConnecter::sendToSchedGetLedOffset()
{
    double _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
    return _t0;
}

// SIGNAL 10
QString QmlConnecter::sendToSchedGetMaterialOption(QString _t1)
{
    QString _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
    return _t0;
}

// SIGNAL 11
QString QmlConnecter::sendToSchedGetPrintOption()
{
    QString _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
    return _t0;
}

// SIGNAL 12
QString QmlConnecter::sendToSchedGetInfoSetting(QString _t1)
{
    QString _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
    return _t0;
}

// SIGNAL 13
void QmlConnecter::sendToSchedSetTotalPrintTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void QmlConnecter::sendToSchedPrintFinishError()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void QmlConnecter::sendToSchedSetHeightOffset(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void QmlConnecter::sendToSchedSetLedOffset(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
bool QmlConnecter::isCustom(QString _t1)
{
    bool _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
    return _t0;
}

// SIGNAL 18
void QmlConnecter::sendToSchedBusySet(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void QmlConnecter::sendToSchedShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void QmlConnecter::sendToSchedGoHome()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void QmlConnecter::sendToSchedAutoHome()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void QmlConnecter::sendToSchedMoveMicro(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void QmlConnecter::sendToSchedMoveMaxHeight()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void QmlConnecter::sendToSchedGetVersion()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void QmlConnecter::sendToSchedGetModelNo()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void QmlConnecter::sendToSchedSetPrintTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void QmlConnecter::receiveFromUpdaterFirmUpdate(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
