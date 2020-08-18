QT += quick
QT += qml
QT += serialport
QT += svg
QT += network
QT += websockets

CONFIG += c++11
#CONFIG += c++1z

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
    bedcontrol.cpp \
    bedserialport.cpp \
    filevalidator.cpp \
    kinetimecalc.cpp \
    logger.cpp \
    main.cpp \
    modelno.cpp \
    networkcontrol.cpp \
    printscheduler.cpp \
    printsetting.cpp \
    resinsetting.cpp \
    resinupdater.cpp \
    updater.cpp \
    version.cpp \
    websocketclient.cpp \
    ymodem.cpp \
    zip/zip.cpp

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
    Singleton.h \
    bedcontrol.h \
    bedserialport.h \
    common.h \
    filevalidator.h \
    kinetimecalc.h \
    logger.h \
    modelno.h \
    networkcontrol.h \
    printscheduler.h \
    printsetting.h \
    resinsetting.h \
    resinupdater.h \
    slate-global.h \
    updater.h \
    version.h \
    websocketclient.h \
    ymodem.h \
    zip/zip.h
#    zip/zip_file.hpp
