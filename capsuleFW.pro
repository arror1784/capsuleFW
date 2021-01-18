QT += quick
QT += qml
QT += serialport
QT += svg
QT += network
QT += websockets

#CONFIG += c++11
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FilesystemModel.cpp \
    VKeyboard/basekeyboard.cpp \
    VKeyboard/engkeyboard.cpp \
    VKeyboard/extrakeyboard.cpp \
    VKeyboard/keyboardsymbols.cpp \
    VKeyboard/keyboardtextcorrector.cpp \
    VKeyboard/keyboardwidget.cpp \
    VKeyboard/specialchkeyboard.cpp \
    bedcontrol.cpp \
    bedserialport.cpp \
    common/jsonreadsetting.cpp \
    common/jsonsetting.cpp \
    common/jsonutil.cpp \
    common/jsonwritesetting.cpp \
    filevalidator.cpp \
    infosetting.cpp \
    kinetimecalc.cpp \
    logger.cpp \
    main.cpp \
    modelno.cpp \
    networkcontrol.cpp \
    printersetting.cpp \
    printscheduler.cpp \
    qmlconnecter.cpp \
    resinsetting.cpp \
    resinupdater.cpp \
    schedulerthread.cpp \
    transimagergb.cpp \
    updateconnector.cpp \
    updater.cpp \
    version.cpp \
    websocketclient.cpp \
    wifiinfo.cpp \
    wpa.cpp \
    wpa_ctrl/common.c \
    wpa_ctrl/os_unix.c \
    wpa_ctrl/wpa_ctrl.c \
    wpa_ctrl/wpa_debug.c \
    ymodem.cpp \
    zip/zip.cpp \
    zipcontrol.cpp

RESOURCES += qml.qrc \
    font.qrc \
    image.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    FilesystemModel.h \
    Singleton.h \
    VKeyboard/basekeyboard.h \
    VKeyboard/engkeyboard.h \
    VKeyboard/extrakeyboard.h \
    VKeyboard/keyboardsymbols.h \
    VKeyboard/keyboardtextcorrector.h \
    VKeyboard/keyboardwidget.h \
    VKeyboard/specialchkeyboard.h \
    bedcontrol.h \
    bedserialport.h \
    common.h \
    common/jsonreadsetting.h \
    common/jsonsetting.h \
    common/jsonutil.h \
    common/jsonwritesetting.h \
    filevalidator.h \
    infosetting.h \
    kinetimecalc.h \
    logger.h \
    modelno.h \
    networkcontrol.h \
    printersetting.h \
    printscheduler.h \
    qmlconnecter.h \
    resinsetting.h \
    resinupdater.h \
    schedulerthread.h \
    transimagergb.h \
    updateconnector.h \
    updater.h \
    version.h \
    websocketclient.h \
    wifiinfo.h \
    wpa.h \
    wpa_ctrl/build_config.h \
    wpa_ctrl/common.h \
    wpa_ctrl/ieee802_11_defs.h \
    wpa_ctrl/includes.h \
    wpa_ctrl/os.h \
    wpa_ctrl/os.h \
    wpa_ctrl/wpa_ctrl.h \
    wpa_ctrl/wpa_debug.h \
    wpa_ctrl/wpabuf.h \
    ymodem.h \
    zip/zip.h \
    zipcontrol.h
#    zip/zip_file.hpp

FORMS += \
    VKeyboard/engkeyboard.ui \
    VKeyboard/extrakeyboard.ui \
    VKeyboard/keyboardwidget.ui \
    VKeyboard/specialchkeyboard.ui
