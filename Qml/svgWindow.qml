import QtQuick 2.0
import QtQuick.Window 2.11
import QtQml 2.0

Window {
    id: svgWindow
    visible: true
    visibility: Window.FullScreen
    width: 1920
    height: 1080
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
//            width: parent.width
//            height: parent.height
//            sourceSize.height: parent.height
//            sourceSize.width: parent.width
//            source: "file:///home/hix/0.svg"
            anchors.centerIn: parent
//            anchors.top: parent.top
//            anchors.left: parent.left
//            anchors.leftMargin: 50
            visible: true
            onStatusChanged: {
                if (printImage.status === Image.Ready){
//                    currentDate = new Date()
//                    console.log("sec : " + currentDate.getSeconds() + " milli : " + currentDate.getMilliseconds())
//                    scheduler.receiveFromQmlImageLoaded('A')
                }
            }
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
        onSendToQmlSetVisibleImage:{
            printImage.visible = visible
        }
    }
}
