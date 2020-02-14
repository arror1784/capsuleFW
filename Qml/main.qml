import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.4

Window {
    id: mainWindow
    visible: true
    visibility: Window.FullScreen
    width: 800
    height: 480
    title: qsTr("Hello World")
    color: "#ffffff"
    screen: Qt.application.screens[1]
    x: screen.virtualX + ((screen.width - width) / 2)
    y: screen.virtualY + ((screen.height - height) / 2)

    Rectangle{
        Button{
            id: printButton
            width: 152
            height: 43
            text: "print"
            anchors.leftMargin: 8
            anchors.topMargin: 8
            anchors.top: parent.top
            anchors.left: parent.left
            onClicked: {
//                scheduler.receiveFromQmlBedPrintStart('A')
//                scheduler.receiveFromSerialPort(bedChar.charAt(0),100)
                if(printButton.text === "print"){
                    fileselect.openPopUp()
                }else if(printButton.text === "pause"){
                    scheduler.receiveFromQmlBedPrintPause('A')
                    enabled = false
                }else if(printButton.text === "resume"){
                    scheduler.receiveFromQmlBedPrintStart('A')
                    text = "pause"
                    stopButton.enabled = false
                }
            }
        }
        Text {
            id: printPathName
            text: ""
            font.pixelSize: 20
            anchors.leftMargin: 8
            anchors.topMargin: 8
            anchors.top: parent.top
            anchors.left: printButton.right
        }
        Button{
            id: stopButton
            width: 152
            height: 43
            text: "stop"
            anchors.leftMargin: 8
            anchors.topMargin: 8
            anchors.top: printButton.bottom
            anchors.left: parent.left
            enabled: false
            onClicked: {
//                scheduler.receiveFromQmlBedPrintStart('A')
//                scheduler.receiveFromSerialPort(bedChar.charAt(0),100)
                scheduler.receiveFromQmlBedPrintFinish('A')
                enabled = false
            }
        }
        Text {
            id: progressText
            width: 27
            height: 0
            text: 0 + " / " + 0
            anchors.topMargin: 15
            font.pixelSize: 20
            anchors.top: stopButton.bottom
            anchors.left: stopButton.left
        }
    }
    Connections{
        id: schedulerConnection
        target: scheduler
        onSendToQmlPauseFinish :{
            printButton.text = "resume"
            printButton.enabled = true
            stopButton.enabled = true
        }
        onSendToQmlPrintFinish :{
            printButton.text = "print"
            printButton.enabled = true
            progressText.text = 0 + "/" + 0
        }
        onSendToQmlUpdateProgress :{
            progressText.text = currentIndex + "/" + maxIndex
        }
    }
    FileSelectPopUp{
        id: fileselect
        onChooseFile: {
            console.debug(filePath)
            printButton.text = "pause"
//            printButton.enabled = false
            stopButton.enabled = false
            scheduler.receiveFromQmlBedPrint('A',filePath)
            printPathName.text = "print name : " + fileName
        }
        onCancleChoose: {
            console.debug("file choose cancle")
        }
    }
}
