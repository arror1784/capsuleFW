import QtQuick 2.9
import QtQuick.Window 2.11
import QtQuick.Controls 1.4

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 350
    title: qsTr("Hello World")
    color: "#0f0f0f"
    screen: Qt.application.screens[0]
    property string bedChar: "A"
    Rectangle{
        anchors.fill: parent
        Text {
            id: accelSpeedText
            text: qsTr("accel speed")
            font.pixelSize: 30
        }
        TextArea{
            id: accelSpeedEdit
            x: -2
            focus: true
            width: 100
            height: 33
            font.letterSpacing: -0.1
            font.capitalization: Font.AllUppercase
            font.pixelSize: 20
            font.bold: true
            anchors.top: accelSpeedText.bottom
            anchors.left: accelSpeedText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
            onEditingFinished: {
//                console.debug(parseInt(text.toString()))
            }
            clip: true
            KeyNavigation.tab: decelSpeedEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: decelSpeedText
            text: qsTr("decel speed")
            font.pixelSize: 30
            anchors.left: accelSpeedText.right
            anchors.leftMargin: 20
        }
        TextArea{
            id: decelSpeedEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: decelSpeedText.bottom
            anchors.left: decelSpeedText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: maxSpeedEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: maxSpeedText
            text: qsTr("max speed")
            font.pixelSize: 30
            anchors.left: decelSpeedText.right
            anchors.leftMargin: 20
        }
        TextArea{
            id: maxSpeedEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: maxSpeedText.bottom
            anchors.left: maxSpeedText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: minSpeedEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: minSpeedText
            text: qsTr("min speed")
            font.pixelSize: 30
            anchors.left: maxSpeedText.right
            anchors.leftMargin: 20
        }
        TextArea{
            id: minSpeedEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: minSpeedText.bottom
            anchors.left: minSpeedText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: bedCuringTimeEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: bedCuringTimeText
            text: qsTr("current time")
            anchors.top: accelSpeedEdit.bottom
            anchors.left: parent.left
            anchors.topMargin: 20
            font.pixelSize: 30
        }
        TextArea{
            id: bedCuringTimeEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: bedCuringTimeText.bottom
            anchors.left: bedCuringTimeText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: curingTimeEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: curingTimeText
            text: qsTr("bed curing time")
            anchors.top: bedCuringTimeText.top
            anchors.left: bedCuringTimeText.right
            anchors.leftMargin: 20
            font.pixelSize: 30
        }
        TextArea{
            id: curingTimeEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: curingTimeText.bottom
            anchors.left: curingTimeText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: zHopHeightEdit

            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: zHopHeightText
            text: qsTr("z hop height")
            anchors.top: curingTimeText.top
            anchors.left: curingTimeText.right
            anchors.leftMargin: 20
            font.pixelSize: 30
        }
        TextArea{
            id: zHopHeightEdit
            focus: true
            width: 100
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: zHopHeightText.bottom
            anchors.left: zHopHeightText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: accelSpeedEdit
            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }
        Text {
            id: commandText
            text: qsTr("send command text")
            anchors.top: bedCuringTimeEdit.bottom
            anchors.left: bedCuringTimeEdit.left
            anchors.leftMargin: 20
            font.pixelSize: 30
        }
        TextArea{
            id: commandTextEdit
            focus: true
            width: 400
            height: 33
            font.pixelSize: 20
            font.bold: true
            anchors.top: commandText.bottom
            anchors.left: commandText.left
            anchors.topMargin: 20
            wrapMode: TextEdit.Wrap
//            onEditingFinished: console.debug(text)
            clip: true
            KeyNavigation.tab: accelSpeedEdit
            Rectangle{
                anchors.fill: parent
                color: "#d0d0d0"
                z: -1
            }
        }

        Button{
            id: updateButton
            width: 60
            height: 40
            text: "update"
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.top: curingTimeText.top
            MouseArea{
                id: updatebuttonMA
                anchors.fill: parent
                onClicked: {
                    scheduler.receiveFromQmlBedConfig('A',parseInt(accelSpeedEdit.text.toString()),parseInt(decelSpeedEdit.text.toString()),
                                                      parseInt(maxSpeedEdit.text.toString()),parseInt(minSpeedEdit.text.toString()),
                                                      parseInt(bedCuringTimeEdit.text.toString()),parseInt(curingTimeEdit.text.toString()),
                                                      parseInt(zHopHeightEdit.text.toString()))
//                    scheduler.receiveFromQmlBedSetBedPath('A',filePathEdit.text)
                }
            }
        }
        Button{
            id: printButton
            width: 60
            height: 40
            text: "print"
            anchors.top: updateButton.bottom
            anchors.left: updateButton.left

            MouseArea{
                anchors.fill: parent
                onClicked: {
//                    scheduler.receiveFromQmlBedPrintStart('A')
                    scheduler.receiveFromSerialPort(bedChar.charAt(0),100)
                }
            }
        }
        Button{
            id: sendCommandButton
            width: 60
            height: 40
            text: "send"
            anchors.top: printButton.bottom
            anchors.left: printButton.left

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    scheduler.receiveFromQmlSendCommand('A',commandTextEdit.text.toString());
                }
            }
        }
        Button{
            id: restartButton
            width: 60
            height: 40
            text: "restart"
            anchors.top: sendCommandButton.bottom
            anchors.left: sendCommandButton.left

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    scheduler.receiveFromSerialPort(bedChar.charAt(0),101)
                }
            }
        }
    }
    Connections{
        id: schedulerConnection
        target: scheduler

        onSendToQmlSetConfig:{
            mainWindow.setConfig(bedChar,accel,decel,max,min,bedCuringTime,curingTime,zHopHeight)
        }
    }

    function setConfig(bedChar,accel,decel,max,min,bedCuringTime,curingTime,zHopHeight){
        if(accel !== -1)
            accelSpeedEdit.text = accel.toString()
        if(decel !== -1)
            decelSpeedEdit.text = decel.toString()
        if(max !== -1)
            maxSpeedEdit.text = max.toString()
        if(min !== -1)
            minSpeedEdit.text = min.toString()
        if(bedCuringTime !== -1)
            bedCuringTimeEdit.text = bedCuringTime.toString()
        if(curingTime !== -1)
            curingTimeEdit.text = curingTime.toString()
        if(zHopHeight !== -1)
            zHopHeightEdit.text = zHopHeight.toString()
    }
}
