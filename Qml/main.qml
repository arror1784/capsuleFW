import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.LocalStorage 2.12
import QtQuick.Window 2.11
import QtQuick.VirtualKeyboard 2.1

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

    signal sendToBusySet(bool value)
    signal wifiConnectCheck()

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: MainMenu{
            property var name: "mainMenu"
            id: mainMenu
        }
        onCurrentItemChanged: {

            if(currentItem.name === "mainMenu"){
                sendToBusySet(false)
            }else if(currentItem.name === "usbPortOpenError"){
                sendToBusySet(true)
            }else{
                sendToBusySet(true)
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

    }
    Image {
        id: networkImage
        width: 20
        height: 20

        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5


        source: "qrc:/image/network.png"
        visible: true
//        scale: 0.1
    }
        function receivePrintSettingError(code){
//            stackView.pop(mainMenu,StackView.Immediate)
            errorPopup.open(code)
        }
        function receiveExitError(){
            busyErrorPopup.open()
        }
        function receiveExit(){
            shutDownPopup.open()
        }
        function receiveLCDState(state){

            if(state){
                lcdOff.close()
            }else{
                lcdOff.open()
            }
        }
        function receivePortOpenError(){
            if(stackView.currentItem.name !== "USBPortOpenError")
                stackView.push(Qt.resolvedUrl("qrc:/Qml/USBPortOpenError.qml"),StackView.Immediate)
        }
        function receiveChangeToPrint(){
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
    function wifiConnectedChange(connected){
        if(connected){
            networkImage.visible = true;
        }else{
            networkImage.visible = false;
        }
    }
    Component.onCompleted: {
        scheduler.sendToUIPrintSettingError.connect(receivePrintSettingError)
        scheduler.sendToUIExitError.connect(receiveExitError)
        scheduler.sendToUIExit.connect(receiveExit)
        scheduler.sendToUILCDState.connect(receiveLCDState)
        scheduler.sendToUIPortOpenError.connect(receivePortOpenError)
        scheduler.sendToUIChangeToPrint(receiveChangeToPrint)

        sendToBusySet.connect(scheduler.receiveFromUIBusySet)

        wifi.connectedChange.connect(wifiConnectedChange)
        wifiConnectCheck.connect(wifi.checkNetworkConnect)

//        shutDownPopup.sendToShutdown.connect(scheduler.receiveFromUIShutdown)

        wifiConnectCheck()
    }
}
