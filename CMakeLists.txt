cmake_minimum_required(VERSION 3.5)

# set(CMAKE_INSTALL_RPATH "/usr/bin/arm-linux-gnueabihf-ld")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)

set(PROJECT_NAME capsuleFW)
project(${PROJECT_NAME}) # Your project name

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)   
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

LINK_LIBRARIES( -lpthread)

# if (${Qt5_FOUND})
#     message("Found Qt " ${Qt5_VERSION})
# else()
#     message("Couldn't find Qt")
# endif()

hunter_add_package(Qt)
message(STATUS"qt base build done")

# find_package(Qt5Core REQUIRED)
# find_package(Qt5 COMPONENTS Widgets REQUIRED)
# find_package(Qt5SerialPort REQUIRED)
# find_package(Qt5Network REQUIRED)
# find_package(Qt5Quick REQUIRED)
# find_package(Qt5Gui REQUIRED)
# find_package(Qt5Qml REQUIRED)
# find_package(Qt5WebSockets REQUIRED)


set(SOURCES
bedcontrol.cpp
bedserialport.cpp
common/jsonreadsetting.cpp
common/jsonsetting.cpp
common/jsonutil.cpp
common/jsonwritesetting.cpp
filevalidator.cpp
infosetting.cpp
kinetimecalc.cpp
logger.cpp
main.cpp
modelno.cpp
networkcontrol.cpp
printersetting.cpp
printscheduler.cpp
resinsetting.cpp
resinupdater.cpp
updater.cpp
version.cpp
websocketclient.cpp
wifiinfo.cpp
wpa.cpp
wpa_ctrl/common.c
wpa_ctrl/os_unix.c# cmake/Hunter/config.cmake
hunter_config(GTest VERSION 1.7.0-hunter-9 CMAKE_ARGS GTEST_SUPER_MODE=ON)
hunter_config(ZLIB VERSION 1.2.8-hunter-1 CMAKE_ARGS ZLIB_FEATURES=FEATURE1;FEATURE2)
wpa_ctrl/wpa_ctrl.c
wpa_ctrl/wpa_debug.c
ymodem.cpp
zip/zip.cpp
qmlconnecter.cpp
qmlconnecter.h
Singleton.h
bedcontrol.h
bedserialport.h
schedulerthread.h
schedulerthread.cpp
common.h
common/jsonreadsetting.h
common/jsonsetting.h
common/jsonutil.h
common/jsonwritesetting.h
filevalidator.h
infosetting.h
kinetimecalc.h
logger.h
modelno.h
networkcontrol.h
printersetting.h
printscheduler.h
resinsetting.h
resinupdater.h
updater.h
version.h
websocketclient.h
wifiinfo.h
wpa.h
wpa_ctrl/build_config.h
wpa_ctrl/common.h
wpa_ctrl/ieee802_11_defs.h
wpa_ctrl/includes.h
wpa_ctrl/os.h
wpa_ctrl/os.h
wpa_ctrl/wpa_ctrl.h
wpa_ctrl/wpa_debug.h
wpa_ctrl/wpabuf.h
ymodem.h
zip/zip.h
zipcontrol.cpp
zipcontrol.h
schedulerthread.h
schedulerthread.cpp
FilesystemModel.h
FilesystemModel.cpp
updateconnector.h
updateconnector.cpp
qml.qrc
font.qrc
image.qrc
factoryreset.cpp
factoryreset.h
hdmicontrol.cpp
hdmicontrol.h
l10imageprovider.cpp
l10imageprovider.h
l10printimage.cpp
l10printimage.h
printimagecontrol.cpp
printimagecontrol.h
transimagergb.cpp
transimagergb.h
c10printimage.cpp
c10printimage.h
productsetting.cpp
productsetting.h
VKeyboard/basekeyboard.cpp
VKeyboard/basekeyboard.h
VKeyboard/engkeyboard.cpp
VKeyboard/engkeyboard.h
VKeyboard/extrakeyboard.cpp
VKeyboard/extrakeyboard.h
VKeyboard/keyboardsymbols.cpp
VKeyboard/keyboardsymbols.h
VKeyboard/keyboardtextcorrector.cpp
VKeyboard/keyboardtextcorrector.h
VKeyboard/keyboardwidget.cpp
VKeyboard/keyboardwidget.h
VKeyboard/specialchkeyboard.cpp
VKeyboard/specialchkeyboard.h
#    zip/zip_file.hpp
)
set(UIS
VKeyboard/specialchkeyboard.ui
VKeyboard/keyboardwidget.ui
VKeyboard/extrakeyboard.ui
VKeyboard/engkeyboard.ui
)

# QT5_WRAP_UI( UI_HEADERS ${UIS} )

add_executable( ${PROJECT_NAME} WIN32  ${SOURCES} ${UIS})

target_link_libraries(${PROJECT_NAME}
Qt5::Widgets
Qt5::Network
Qt5::Gui
Qt5::Qml
Qt5::WebSockets 
Qt5::Quick
Qt5::SerialPort
)
