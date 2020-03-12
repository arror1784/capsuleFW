import QtQuick 2.0
import QtQuick.Window 2.11
import QtQml 2.0

Window {
    id: svgWindow
    visible: true
    visibility: Window.FullScreen
//    width: 1440
//    height: 2560
    title: qsTr("Hello World")
    color: "#000000"
    screen: Qt.application.screens[0]
    x: screen.virtualX
    y: screen.virtualY
//    flags: Qt.WindowStaysOnTopHint

//    Rectangle{
//        width: parent.width
//        height: parent.height
//        color: "#000000"
        Image{
            id: printImage
            width: 2560
            height: 1440
//            sourceSize.height: parent.height
//            sourceSize.width: parent.width
            anchors.centerIn: parent
//            anchors.fill: parent

            visible: true

            fillMode: Image.PreserveAspectCrop

            rotation: 90
        }
//    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.BlankCursor
    }
    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlChangeImage:{
            console.log(imagePath)
            printImage.source = imagePath
        }
        onSendToQmlSetImageScale:{
            printImage.scale = value
            console.debug(value)
        }
    }
}
