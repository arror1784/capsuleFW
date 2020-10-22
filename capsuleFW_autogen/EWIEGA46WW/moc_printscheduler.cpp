/****************************************************************************
** Meta object code from reading C++ file 'printscheduler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../printscheduler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printscheduler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrintScheduler_t {
    QByteArrayData data[90];
    char stringdata0[1709];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrintScheduler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrintScheduler_t qt_meta_stringdata_PrintScheduler = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PrintScheduler"
QT_MOC_LITERAL(1, 15, 20), // "sendToLCDChangeImage"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 9), // "imagePath"
QT_MOC_LITERAL(4, 47, 22), // "sendToLCDSetImageScale"
QT_MOC_LITERAL(5, 70, 5), // "value"
QT_MOC_LITERAL(6, 76, 22), // "sendToUIUpdateProgress"
QT_MOC_LITERAL(7, 99, 8), // "progress"
QT_MOC_LITERAL(8, 108, 23), // "sendToUIFirstlayerStart"
QT_MOC_LITERAL(9, 132, 24), // "sendToUIFirstlayerFinish"
QT_MOC_LITERAL(10, 157, 21), // "sendToUIChangeToPrint"
QT_MOC_LITERAL(11, 179, 26), // "sendToUIChangeToPauseStart"
QT_MOC_LITERAL(12, 206, 27), // "sendToUIChangeToPauseFinish"
QT_MOC_LITERAL(13, 234, 22), // "sendToUIChangeToResume"
QT_MOC_LITERAL(14, 257, 20), // "sendToUIChangeToQuit"
QT_MOC_LITERAL(15, 278, 27), // "sendToUIChangeToPrintFinish"
QT_MOC_LITERAL(16, 306, 30), // "sendToUIChangeToPrintWorkError"
QT_MOC_LITERAL(17, 337, 36), // "sendToUIChangeToPrintWorkErro..."
QT_MOC_LITERAL(18, 374, 19), // "sendToUIChangeState"
QT_MOC_LITERAL(19, 394, 5), // "state"
QT_MOC_LITERAL(20, 400, 25), // "sendToUIPrintSettingError"
QT_MOC_LITERAL(21, 426, 4), // "code"
QT_MOC_LITERAL(22, 431, 19), // "sendToUIEnableTimer"
QT_MOC_LITERAL(23, 451, 6), // "enable"
QT_MOC_LITERAL(24, 458, 20), // "sendToUIMaterialList"
QT_MOC_LITERAL(25, 479, 4), // "name"
QT_MOC_LITERAL(26, 484, 17), // "sendToUIPrintInfo"
QT_MOC_LITERAL(27, 502, 12), // "printerState"
QT_MOC_LITERAL(28, 515, 8), // "material"
QT_MOC_LITERAL(29, 524, 8), // "fileName"
QT_MOC_LITERAL(30, 533, 11), // "layerHeight"
QT_MOC_LITERAL(31, 545, 11), // "elapsedTime"
QT_MOC_LITERAL(32, 557, 9), // "totalTime"
QT_MOC_LITERAL(33, 567, 11), // "enableTimer"
QT_MOC_LITERAL(34, 579, 20), // "sendToUISetTotalTime"
QT_MOC_LITERAL(35, 600, 4), // "time"
QT_MOC_LITERAL(36, 605, 21), // "sendToUIPortOpenError"
QT_MOC_LITERAL(37, 627, 16), // "sendToUILCDState"
QT_MOC_LITERAL(38, 644, 17), // "sendToUIExitError"
QT_MOC_LITERAL(39, 662, 12), // "sendToUIExit"
QT_MOC_LITERAL(40, 675, 14), // "sendToUIMoveOk"
QT_MOC_LITERAL(41, 690, 25), // "MCUFirmwareUpdateFinished"
QT_MOC_LITERAL(42, 716, 25), // "sendToUISWUpdateAvailable"
QT_MOC_LITERAL(43, 742, 28), // "sendToUISWUpdateNotAvailable"
QT_MOC_LITERAL(44, 771, 24), // "sendToUISWUpdateFinished"
QT_MOC_LITERAL(45, 796, 21), // "sendToUISWUpdateError"
QT_MOC_LITERAL(46, 818, 20), // "sendToUIHeightOffset"
QT_MOC_LITERAL(47, 839, 6), // "offset"
QT_MOC_LITERAL(48, 846, 17), // "sendToUILEDOffset"
QT_MOC_LITERAL(49, 864, 22), // "sendToUIMaterialOption"
QT_MOC_LITERAL(50, 887, 6), // "option"
QT_MOC_LITERAL(51, 894, 22), // "sendToUIGetPrintOption"
QT_MOC_LITERAL(52, 917, 22), // "sendToUIGetInfoSetting"
QT_MOC_LITERAL(53, 940, 4), // "path"
QT_MOC_LITERAL(54, 945, 16), // "sendToUIIsCustom"
QT_MOC_LITERAL(55, 962, 15), // "sendToUIVersion"
QT_MOC_LITERAL(56, 978, 7), // "version"
QT_MOC_LITERAL(57, 986, 15), // "sendToUIModelNo"
QT_MOC_LITERAL(58, 1002, 7), // "modelNo"
QT_MOC_LITERAL(59, 1010, 24), // "receiveFromQMLPrintStart"
QT_MOC_LITERAL(60, 1035, 12), // "materialName"
QT_MOC_LITERAL(61, 1048, 23), // "receiveFromUIPrintStart"
QT_MOC_LITERAL(62, 1072, 4), // "byte"
QT_MOC_LITERAL(63, 1077, 23), // "receiveFromUIPrintAgain"
QT_MOC_LITERAL(64, 1101, 29), // "receiveFromUIPrintStateChange"
QT_MOC_LITERAL(65, 1131, 3), // "CMD"
QT_MOC_LITERAL(66, 1135, 28), // "receiveFromUIGetMaterialList"
QT_MOC_LITERAL(67, 1164, 30), // "receiveFromUIGetPrintInfoToWeb"
QT_MOC_LITERAL(68, 1195, 28), // "receiveFromUIGetHeightOffset"
QT_MOC_LITERAL(69, 1224, 25), // "receiveFromUIGetLedOffset"
QT_MOC_LITERAL(70, 1250, 30), // "receiveFromUIGetMaterialOption"
QT_MOC_LITERAL(71, 1281, 27), // "receiveFromUIGetPrintOption"
QT_MOC_LITERAL(72, 1309, 27), // "receiveFromUIGetInfoSetting"
QT_MOC_LITERAL(73, 1337, 30), // "receiveFromUISetTotalPrintTime"
QT_MOC_LITERAL(74, 1368, 29), // "receiveFromUIPrintFinishError"
QT_MOC_LITERAL(75, 1398, 28), // "receiveFromUISetHeightOffset"
QT_MOC_LITERAL(76, 1427, 25), // "receiveFromUISetLedOffset"
QT_MOC_LITERAL(77, 1453, 8), // "isCustom"
QT_MOC_LITERAL(78, 1462, 20), // "receiveFromUIBusySet"
QT_MOC_LITERAL(79, 1483, 2), // "bs"
QT_MOC_LITERAL(80, 1486, 21), // "receiveFromUIShutdown"
QT_MOC_LITERAL(81, 1508, 19), // "receiveFromUIGoHome"
QT_MOC_LITERAL(82, 1528, 21), // "receiveFromUIAutoHome"
QT_MOC_LITERAL(83, 1550, 26), // "receiveFromUIMoveMaxHeight"
QT_MOC_LITERAL(84, 1577, 22), // "receiveFromUIMoveMicro"
QT_MOC_LITERAL(85, 1600, 5), // "micro"
QT_MOC_LITERAL(86, 1606, 23), // "receiveFromUIGetVersion"
QT_MOC_LITERAL(87, 1630, 23), // "receiveFromUIGetModelNo"
QT_MOC_LITERAL(88, 1654, 25), // "receiveFromUISetPrintTime"
QT_MOC_LITERAL(89, 1680, 28) // "receiveFromUpdaterFirmUpdate"

    },
    "PrintScheduler\0sendToLCDChangeImage\0"
    "\0imagePath\0sendToLCDSetImageScale\0"
    "value\0sendToUIUpdateProgress\0progress\0"
    "sendToUIFirstlayerStart\0"
    "sendToUIFirstlayerFinish\0sendToUIChangeToPrint\0"
    "sendToUIChangeToPauseStart\0"
    "sendToUIChangeToPauseFinish\0"
    "sendToUIChangeToResume\0sendToUIChangeToQuit\0"
    "sendToUIChangeToPrintFinish\0"
    "sendToUIChangeToPrintWorkError\0"
    "sendToUIChangeToPrintWorkErrorFinish\0"
    "sendToUIChangeState\0state\0"
    "sendToUIPrintSettingError\0code\0"
    "sendToUIEnableTimer\0enable\0"
    "sendToUIMaterialList\0name\0sendToUIPrintInfo\0"
    "printerState\0material\0fileName\0"
    "layerHeight\0elapsedTime\0totalTime\0"
    "enableTimer\0sendToUISetTotalTime\0time\0"
    "sendToUIPortOpenError\0sendToUILCDState\0"
    "sendToUIExitError\0sendToUIExit\0"
    "sendToUIMoveOk\0MCUFirmwareUpdateFinished\0"
    "sendToUISWUpdateAvailable\0"
    "sendToUISWUpdateNotAvailable\0"
    "sendToUISWUpdateFinished\0sendToUISWUpdateError\0"
    "sendToUIHeightOffset\0offset\0"
    "sendToUILEDOffset\0sendToUIMaterialOption\0"
    "option\0sendToUIGetPrintOption\0"
    "sendToUIGetInfoSetting\0path\0"
    "sendToUIIsCustom\0sendToUIVersion\0"
    "version\0sendToUIModelNo\0modelNo\0"
    "receiveFromQMLPrintStart\0materialName\0"
    "receiveFromUIPrintStart\0byte\0"
    "receiveFromUIPrintAgain\0"
    "receiveFromUIPrintStateChange\0CMD\0"
    "receiveFromUIGetMaterialList\0"
    "receiveFromUIGetPrintInfoToWeb\0"
    "receiveFromUIGetHeightOffset\0"
    "receiveFromUIGetLedOffset\0"
    "receiveFromUIGetMaterialOption\0"
    "receiveFromUIGetPrintOption\0"
    "receiveFromUIGetInfoSetting\0"
    "receiveFromUISetTotalPrintTime\0"
    "receiveFromUIPrintFinishError\0"
    "receiveFromUISetHeightOffset\0"
    "receiveFromUISetLedOffset\0isCustom\0"
    "receiveFromUIBusySet\0bs\0receiveFromUIShutdown\0"
    "receiveFromUIGoHome\0receiveFromUIAutoHome\0"
    "receiveFromUIMoveMaxHeight\0"
    "receiveFromUIMoveMicro\0micro\0"
    "receiveFromUIGetVersion\0receiveFromUIGetModelNo\0"
    "receiveFromUISetPrintTime\0"
    "receiveFromUpdaterFirmUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrintScheduler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      63,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      37,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  329,    2, 0x06 /* Public */,
       4,    1,  332,    2, 0x06 /* Public */,
       6,    1,  335,    2, 0x06 /* Public */,
       8,    0,  338,    2, 0x06 /* Public */,
       9,    0,  339,    2, 0x06 /* Public */,
      10,    0,  340,    2, 0x06 /* Public */,
      11,    0,  341,    2, 0x06 /* Public */,
      12,    0,  342,    2, 0x06 /* Public */,
      13,    0,  343,    2, 0x06 /* Public */,
      14,    0,  344,    2, 0x06 /* Public */,
      15,    0,  345,    2, 0x06 /* Public */,
      16,    0,  346,    2, 0x06 /* Public */,
      17,    0,  347,    2, 0x06 /* Public */,
      18,    1,  348,    2, 0x06 /* Public */,
      20,    1,  351,    2, 0x06 /* Public */,
      22,    1,  354,    2, 0x06 /* Public */,
      24,    1,  357,    2, 0x06 /* Public */,
      26,    8,  360,    2, 0x06 /* Public */,
      34,    1,  377,    2, 0x06 /* Public */,
      36,    0,  380,    2, 0x06 /* Public */,
      37,    1,  381,    2, 0x06 /* Public */,
      38,    0,  384,    2, 0x06 /* Public */,
      39,    0,  385,    2, 0x06 /* Public */,
      40,    0,  386,    2, 0x06 /* Public */,
      41,    0,  387,    2, 0x06 /* Public */,
      42,    0,  388,    2, 0x06 /* Public */,
      43,    0,  389,    2, 0x06 /* Public */,
      44,    0,  390,    2, 0x06 /* Public */,
      45,    0,  391,    2, 0x06 /* Public */,
      46,    1,  392,    2, 0x06 /* Public */,
      48,    1,  395,    2, 0x06 /* Public */,
      49,    2,  398,    2, 0x06 /* Public */,
      51,    1,  403,    2, 0x06 /* Public */,
      52,    2,  406,    2, 0x06 /* Public */,
      54,    1,  411,    2, 0x06 /* Public */,
      55,    1,  414,    2, 0x06 /* Public */,
      57,    1,  417,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      59,    2,  420,    2, 0x0a /* Public */,
      61,    3,  425,    2, 0x0a /* Public */,
      63,    0,  432,    2, 0x0a /* Public */,
      64,    1,  433,    2, 0x0a /* Public */,
      66,    0,  436,    2, 0x0a /* Public */,
      67,    0,  437,    2, 0x0a /* Public */,
      68,    0,  438,    2, 0x0a /* Public */,
      69,    0,  439,    2, 0x0a /* Public */,
      70,    1,  440,    2, 0x0a /* Public */,
      71,    0,  443,    2, 0x0a /* Public */,
      72,    1,  444,    2, 0x0a /* Public */,
      73,    1,  447,    2, 0x0a /* Public */,
      74,    0,  450,    2, 0x0a /* Public */,
      75,    1,  451,    2, 0x0a /* Public */,
      76,    1,  454,    2, 0x0a /* Public */,
      77,    1,  457,    2, 0x0a /* Public */,
      78,    1,  460,    2, 0x0a /* Public */,
      80,    0,  463,    2, 0x0a /* Public */,
      81,    0,  464,    2, 0x0a /* Public */,
      82,    0,  465,    2, 0x0a /* Public */,
      83,    0,  466,    2, 0x0a /* Public */,
      84,    1,  467,    2, 0x0a /* Public */,
      86,    0,  470,    2, 0x0a /* Public */,
      87,    0,  471,    2, 0x0a /* Public */,
      88,    1,  472,    2, 0x0a /* Public */,
      89,    1,  475,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Int,    7,
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
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Bool,   23,
    QMetaType::Void, QMetaType::QVariantList,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Bool,   27,   28,   29,   30,   31,   32,    7,   33,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   28,   50,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   53,   50,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString,   56,
    QMetaType::Void, QMetaType::QString,   58,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   53,   60,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QJsonObject,   29,   60,   62,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   65,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Double,
    QMetaType::QString, QMetaType::QString,   28,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QString,   53,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Bool, QMetaType::QString,   53,
    QMetaType::Void, QMetaType::Bool,   79,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   85,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::QString,   53,

       0        // eod
};

void PrintScheduler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PrintScheduler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToLCDChangeImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendToLCDSetImageScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->sendToUIUpdateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sendToUIFirstlayerStart(); break;
        case 4: _t->sendToUIFirstlayerFinish(); break;
        case 5: _t->sendToUIChangeToPrint(); break;
        case 6: _t->sendToUIChangeToPauseStart(); break;
        case 7: _t->sendToUIChangeToPauseFinish(); break;
        case 8: _t->sendToUIChangeToResume(); break;
        case 9: _t->sendToUIChangeToQuit(); break;
        case 10: _t->sendToUIChangeToPrintFinish(); break;
        case 11: _t->sendToUIChangeToPrintWorkError(); break;
        case 12: _t->sendToUIChangeToPrintWorkErrorFinish(); break;
        case 13: _t->sendToUIChangeState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->sendToUIPrintSettingError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->sendToUIEnableTimer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->sendToUIMaterialList((*reinterpret_cast< QVariantList(*)>(_a[1]))); break;
        case 17: _t->sendToUIPrintInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< bool(*)>(_a[8]))); break;
        case 18: _t->sendToUISetTotalTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->sendToUIPortOpenError(); break;
        case 20: _t->sendToUILCDState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->sendToUIExitError(); break;
        case 22: _t->sendToUIExit(); break;
        case 23: _t->sendToUIMoveOk(); break;
        case 24: _t->MCUFirmwareUpdateFinished(); break;
        case 25: _t->sendToUISWUpdateAvailable(); break;
        case 26: _t->sendToUISWUpdateNotAvailable(); break;
        case 27: _t->sendToUISWUpdateFinished(); break;
        case 28: _t->sendToUISWUpdateError(); break;
        case 29: _t->sendToUIHeightOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->sendToUILEDOffset((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 31: _t->sendToUIMaterialOption((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 32: _t->sendToUIGetPrintOption((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->sendToUIGetInfoSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 34: _t->sendToUIIsCustom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->sendToUIVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->sendToUIModelNo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 37: _t->receiveFromQMLPrintStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 38: _t->receiveFromUIPrintStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QJsonObject(*)>(_a[3]))); break;
        case 39: _t->receiveFromUIPrintAgain(); break;
        case 40: _t->receiveFromUIPrintStateChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: _t->receiveFromUIGetMaterialList(); break;
        case 42: _t->receiveFromUIGetPrintInfoToWeb(); break;
        case 43: { int _r = _t->receiveFromUIGetHeightOffset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 44: { double _r = _t->receiveFromUIGetLedOffset();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 45: { QString _r = _t->receiveFromUIGetMaterialOption((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 46: { QString _r = _t->receiveFromUIGetPrintOption();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 47: { QString _r = _t->receiveFromUIGetInfoSetting((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 48: _t->receiveFromUISetTotalPrintTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->receiveFromUIPrintFinishError(); break;
        case 50: _t->receiveFromUISetHeightOffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->receiveFromUISetLedOffset((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 52: { bool _r = _t->isCustom((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 53: _t->receiveFromUIBusySet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->receiveFromUIShutdown(); break;
        case 55: _t->receiveFromUIGoHome(); break;
        case 56: _t->receiveFromUIAutoHome(); break;
        case 57: _t->receiveFromUIMoveMaxHeight(); break;
        case 58: _t->receiveFromUIMoveMicro((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->receiveFromUIGetVersion(); break;
        case 60: _t->receiveFromUIGetModelNo(); break;
        case 61: _t->receiveFromUISetPrintTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: _t->receiveFromUpdaterFirmUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrintScheduler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToLCDChangeImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToLCDSetImageScale)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIUpdateProgress)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIFirstlayerStart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIFirstlayerFinish)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPrint)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPauseStart)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPauseFinish)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToResume)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToQuit)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPrintFinish)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPrintWorkError)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeToPrintWorkErrorFinish)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIChangeState)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIPrintSettingError)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIEnableTimer)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QVariantList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIMaterialList)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString , QString , QString , double , int , int , int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIPrintInfo)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUISetTotalTime)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIPortOpenError)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUILCDState)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIExitError)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIExit)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIMoveOk)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::MCUFirmwareUpdateFinished)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUISWUpdateAvailable)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUISWUpdateNotAvailable)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUISWUpdateFinished)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUISWUpdateError)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIHeightOffset)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUILEDOffset)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIMaterialOption)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIGetPrintOption)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIGetInfoSetting)) {
                *result = 33;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIIsCustom)) {
                *result = 34;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIVersion)) {
                *result = 35;
                return;
            }
        }
        {
            using _t = void (PrintScheduler::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrintScheduler::sendToUIModelNo)) {
                *result = 36;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PrintScheduler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PrintScheduler.data,
    qt_meta_data_PrintScheduler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrintScheduler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrintScheduler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrintScheduler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PrintScheduler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 63)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 63;
    }
    return _id;
}

// SIGNAL 0
void PrintScheduler::sendToLCDChangeImage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PrintScheduler::sendToLCDSetImageScale(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PrintScheduler::sendToUIUpdateProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PrintScheduler::sendToUIFirstlayerStart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PrintScheduler::sendToUIFirstlayerFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PrintScheduler::sendToUIChangeToPrint()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PrintScheduler::sendToUIChangeToPauseStart()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PrintScheduler::sendToUIChangeToPauseFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void PrintScheduler::sendToUIChangeToResume()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void PrintScheduler::sendToUIChangeToQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void PrintScheduler::sendToUIChangeToPrintFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void PrintScheduler::sendToUIChangeToPrintWorkError()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void PrintScheduler::sendToUIChangeToPrintWorkErrorFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void PrintScheduler::sendToUIChangeState(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PrintScheduler::sendToUIPrintSettingError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PrintScheduler::sendToUIEnableTimer(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void PrintScheduler::sendToUIMaterialList(QVariantList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void PrintScheduler::sendToUIPrintInfo(QString _t1, QString _t2, QString _t3, double _t4, int _t5, int _t6, int _t7, bool _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void PrintScheduler::sendToUISetTotalTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void PrintScheduler::sendToUIPortOpenError()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void PrintScheduler::sendToUILCDState(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void PrintScheduler::sendToUIExitError()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}

// SIGNAL 22
void PrintScheduler::sendToUIExit()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void PrintScheduler::sendToUIMoveOk()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void PrintScheduler::MCUFirmwareUpdateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void PrintScheduler::sendToUISWUpdateAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 25, nullptr);
}

// SIGNAL 26
void PrintScheduler::sendToUISWUpdateNotAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}

// SIGNAL 27
void PrintScheduler::sendToUISWUpdateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 27, nullptr);
}

// SIGNAL 28
void PrintScheduler::sendToUISWUpdateError()
{
    QMetaObject::activate(this, &staticMetaObject, 28, nullptr);
}

// SIGNAL 29
void PrintScheduler::sendToUIHeightOffset(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void PrintScheduler::sendToUILEDOffset(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void PrintScheduler::sendToUIMaterialOption(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void PrintScheduler::sendToUIGetPrintOption(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void PrintScheduler::sendToUIGetInfoSetting(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void PrintScheduler::sendToUIIsCustom(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void PrintScheduler::sendToUIVersion(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void PrintScheduler::sendToUIModelNo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
