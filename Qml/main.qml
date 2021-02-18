﻿import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.LocalStorage 2.12
import QtQuick.Window 2.11
import App 1.0

Window {
    id: mainWindow
    visible: true
//    visibility: Window.FullScreen
    width: 480
    height: 320
    title: qsTr("Hello World")
    color: "#EEF5F9"
    screen: Qt.application.screens[1]

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }
    FontLoader{
        id: nanumBarunGothic
        source: "qrc:/fonts/NanumBarunGothic.ttf"
    }

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MainMenu{
            property var name: "mainMenu"
            id: mainMenu
        }
        onCurrentItemChanged: {

            if(currentItem.name === "mainMenu"){
                connection.receiveFromQmlBusySet(false)
            }else if(currentItem.name === "usbPortOpenError"){
                connection.receiveFromQmlBusySet(true)
            }else{
                connection.receiveFromQmlBusySet(true)
            }
        }
    }
    SelectFileEnterFail{
        id: selectFileEnterFail
    }
    ErrorPopup{
        id: errorPopup
        onBack: {
//            stackView.pop(mainMenu,StackView.Immediate)
        }
    }
    BusyErrorPopup{
        id: busyErrorPopup
    }
    LcdOff{
        id: lcdOff
    }
    ShutdownPopup{
        id: shutDownPopup
        onSendToShutdown: {
            connection.receiveFromQmlShutdown()
        }
    }
    Connections{
        target: connection
        onSendToQmlPrintSettingError:{
            errorPopup.open(code)
        }
        onSendToQmlExit:{
            if(error){
                shutDownPopup.open()
            }else{
                busyErrorPopup.open()
            }

        }
        onSendToQmlLCDState:{
            if(state){
                lcdOff.close()
            }else{
                lcdOff.open()
            }
        }
        onSendToQmlPortOpenError:{
            if(value){
                if(stackView.currentItem.name !== "USBPortOpenError")
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/USBPortOpenError.qml"),StackView.Immediate)
            }
        }
        onSendToQmlChangeToPrint:{
            var fileIt = stackView.find(function(item,index){return item.isFileSelectList})
            if(fileIt){
                fileIt.fileCheckDisconnected = false
                console.log("there is fileSelectList")
            }else{
                console.log("there is not fileSelectList")
            }

            var it = stackView.find(function(item,index){return item.isPrinMenu})
            if(stackView.currentItem.isPrinMenu){
                console.debug("isPrintMenu")
            }else{
                if(it === null){
                    stackView.push(Qt.resolvedUrl("qrc:/Qml/PrintMenu.qml"),StackView.Immediate)
                }else{
                    it.clear()
                    stackView.pop(it,StackView.Immediate)
                }
            }
        }
    }
    Component.onCompleted: {
//        sdf.open("asd","asd",0,true)
        connection.receiveFromQmlGetUsbPortError()
    }
}
