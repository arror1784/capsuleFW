import QtQuick 2.12
import QtQuick.Window 2.11
import QtQuick.Controls 2.10

Window {
    id: lcdWindow
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

    Image{
        id: printImage
        width: 2560
        height: 1440
//        asynchronous: true
//            sourceSize.height: parent.height
//            sourceSize.width: parent.width
        anchors.centerIn: parent
//            anchors.fill: parent

        visible: true

        fillMode: Image.PreserveAspectCrop
        source: "qrc:/image/defaultBlackImage.png"
        rotation: 90
        onStatusChanged: {
//            if (printImage.status === Image.Ready) console.log('Loaded')
        }
    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.BlankCursor
    }
    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToLCDChangeImage: {
            console.log(imagePath)
            printImage.source = imagePath
        }
        onSendToLCDSetImageScale: {
            printImage.scale = value
        }
        onSendToUIChangeToPrintWorkErrorFinish:{
            printImage.source = "qrc:/image/defaultBlackImage.png"
        }
        onSendToUIChangeToPrintFinish:{
            printImage.source = "qrc:/image/defaultBlackImage.png"
        }
    }
}
