import QtQuick 2.12
import QtQuick.Controls 2.0
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

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MainMenu{
            property var name: "mainMenu"
            id: mainMenu
        }
        onCurrentItemChanged: {
            if(currentItem.name === "mainMenu"){
                scheduler.receiveFromQmlBusySet(false)
//                printSettingSocket.socketClose()
                console.debug("change to mainmenu")
            }else if(currentItem.name === "usbPortOpenError"){
                scheduler.receiveFromQmlBusySet(false)
//                printSettingSocket.socketClose()
            }else{
                scheduler.receiveFromQmlBusySet(true)
                console.debug("is not mainmenu")
            }
        }
    }
//    PrintSettingSocket{
//        id: printSettingSocket
//        onSocketDisconnect: {
//            scheduler.receiveFromQmlBusySet(false)
//            stackView.pop(mainMenu,StackView.Immediate)
//            selectFileEnterFail.open()
//        }
//        onSocketError: {
////            scheduler.receiveFromQmlBusySet(false)
////            stackView.pop(mainMenu,StackView.Immediate)
//            selectFileEnterFail.setError(true)
////            selectFileEnterFail.open()
//        }
//    }
    SelectFileEnterFail{
        id: selectFileEnterFail
    }
    ErrorPopup{
        id: errorPopup
        onBack: {
            scheduler.receiveFromQmlBusySet(false)
            stackView.pop(mainMenu,StackView.Immediate)
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
    }

    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlPrintSettingError :{
            errorPopup.open()
        }
        onSendToQmlExitError :{
            busyErrorPopup.open()
        }
        onSendToQmlExit:{
            shutDownPopup.open()
        }
        onSendToLCDState:{
            console.debug(state)
            if(state){
                lcdOff.close()
            }else{
                lcdOff.open()
            }
        }
        onSendToQmlPortOpenError:{
            stackView.push(Qt.resolvedUrl("qrc:/Qml/USBPortOpenError.qml"),StackView.Immediate)
        }
    }
}
