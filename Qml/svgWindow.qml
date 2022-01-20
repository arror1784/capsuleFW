import QtQuick 2.12
import QtQuick.Window 2.11
import QtQuick.Controls 2.10

Window {
    id: lcdWindow
    visible: true
    visibility: Window.FullScreen

    title: qsTr("Hello World")
    color: "#000000"
    screen: Qt.application.screens[0]
    x: screen.virtualX
    y: screen.virtualY
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint

    Image{
        id: img
//        asynchronous: true
//            sourceSize.height: parent.height
//            sourceSize.width: parent.width
//        anchors.fill: parent
        anchors.centerIn: parent
//            anchors.fill: parent

        visible: true

        fillMode: Image.PreserveAspectCrop
        source: "qrc:/image/defaultBlackImage.png"
//        rotation: 90
        onStatusChanged: {
            if (img.status === Image.Ready) {
                printImage.imageWrote()
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        cursorShape: Qt.BlankCursor
    }
    Connections{
        target: connection
        onSendToQmlChangeState:{
            if(state === "printFinish"){
                printImage.source = "qrc:/image/defaultBlackImage.png"
            }else if(state === "printErrorFinish"){
                printImage.source = "qrc:/image/defaultBlackImage.png"
            }
        }
    }
    Connections{
        target: printImage
        onSendToQmlChangeImage:{
            console.log(path)
            img.source = path
        }
        onSendToQmlImageScale:{
            console.log("scale",scale)
            img.scale = scale
        }
        onSendToQmlImageRotate:{
            console.log("rotate",rotate)
            img.rotation = rotate
        }
        onSendToQmlImageWidhtHeight:{
            img.width = width
            img.height = height
        }
    }
    Connections{
        target: wac
        onActiveWindow: {
            lcdWindow.requestActivate()
        }
    }
    onActiveChanged: {
        console.log("LCD " + lcdWindow.active)
    }
}
