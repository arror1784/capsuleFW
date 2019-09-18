import QtQuick 2.0
import QtQuick.Window 2.11
import QtQml 2.0

Window {
    id: svgWindow
    visible: true
//    width: 2560
//    height: 1440
    title: qsTr("Hello World")
    color: "#000000"
    screen: Qt.application.screens[1]
//    flags: Qt.WindowStaysOnTopHint

    property date currentDate: new Date()

    Image{
        id: printImage
//        width: parent.width
//        height: parent.height
//        sourceSize.height: parent.height
//        sourceSize.width: parent.width
//        source: "file://~/0.svg"
        anchors.centerIn: parent
        visible: true
        onStatusChanged: {
            if (printImage.status === Image.Ready){
                currentDate = new Date()
//                console.log("sec : " + currentDate.getSeconds() + " milli : " + currentDate.getMilliseconds())
//                scheduler.receiveFromQmlImageLoaded('A')
            }
        }
        onVisibleChanged: {
            if(printImage.visible === true){
                scheduler.receiveFromQmlImageLoaded('A')

            }
        }
        rotation: 90
    }
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
    Component.onCompleted: {
        svgWindow.showFullScreen();
    }
}
