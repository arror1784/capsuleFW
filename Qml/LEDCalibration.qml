import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    width: 480
    height: 320

    property var maxLEDBrightness: 150.0
    property var minLEDBrightness: 50.0
    property var currentLEDBrightness: 0.0

    Text {
        id: calibrationText
        text: qsTr("Calibration")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        width: bedHeightText.contentWidth
        height: bedHeightText.contentHeight + hightNumber.contentHeight + 30

        anchors.left: parent.left
        anchors.leftMargin: (240 - width) / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -20


        color: "#00000000"

        Text {
            id: bedHeightText
            text: qsTr("UV LED Brightness (%)")
            color: "#666666"

            font.pixelSize: 20
            font.family: openSansRegular.name
        }
        Text {
            id: hightNumber

            anchors.top: bedHeightText.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: bedHeightText.horizontalCenter
            text: currentLEDBrightness
            color: "#474747"
            font.pixelSize: 30
            font.family: openSansSemibold.name
        }
    }

    Rectangle{
        id: calibrationButtons

        width: onePlusbutton.width + twoPlusbutton.width + oneText.contentHeight + 10
        height: oneMinbutton.height + onePlusbutton.height + oneText.contentHeight + 10

        anchors.right: parent.right
        anchors.rightMargin: (240 - width) / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -20

        color: "#00000000"
        Button{
            id: onePlusbutton

            width: 45
            height: 45
            background: Rectangle{
                anchors.fill: parent

                color: "#C9DBE6"
                radius: 8
            }
            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/plus.png"
            }
            onClicked: {
                if(currentLEDBrightness < maxLEDBrightness){
                    currentLEDBrightness += 1
                    if(currentLEDBrightness > maxLEDBrightness)
                        currentLEDBrightness = maxLEDBrightness
                }
            }
        }
        Text {
            id: oneText

            anchors.top: onePlusbutton.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: onePlusbutton.horizontalCenter
            text: qsTr("1")
            color: "#9CB5C4"

            font.pixelSize: 20
            font.family: openSansSemibold.name
        }
        Button{
            id: oneMinbutton
            width: 45
            height: 45

            anchors.top: oneText.bottom
            anchors.topMargin: 5

            background: Rectangle{
                anchors.fill: parent

                color: "#C9DBE6"
                radius: 8
            }
            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/minus.png"
            }
            onClicked: {
                if(currentLEDBrightness > minLEDBrightness){
                    currentLEDBrightness -= 1
                    if(currentLEDBrightness < minLEDBrightness)
                        currentLEDBrightness = minLEDBrightness
                }
            }
        }
        Button{
            id: twoPlusbutton

            width: 45
            height: 45

            anchors.left: onePlusbutton.right
            anchors.leftMargin: oneText.contentHeight + 10
            background: Rectangle{
                anchors.fill: parent

                color: "#C9DBE6"
                radius: 8
            }
            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/plus.png"
            }
            onClicked: {
                if(currentLEDBrightness < maxLEDBrightness){
                    currentLEDBrightness += 0.1
                    currentLEDBrightness = Math.round(currentLEDBrightness * 10) / 10
                    if(currentLEDBrightness > maxLEDBrightness)
                        currentLEDBrightness = maxLEDBrightness
                }
            }
        }
        Text {
            id: twoText

            anchors.top: twoPlusbutton.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: twoPlusbutton.horizontalCenter
            text: qsTr("0.1")
            color: "#9CB5C4"

            font.pixelSize: 20
            font.family: openSansSemibold.name
        }
        Button{
            id: twoMinbutton
            width: 45
            height: 45

            anchors.top: twoText.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: twoText.horizontalCenter

            background: Rectangle{
                anchors.fill: parent

                color: "#C9DBE6"
                radius: 8
            }
            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/minus.png"
            }
            onClicked: {
                if(currentLEDBrightness < maxLEDBrightness){
                    currentLEDBrightness -= 0.1
                    currentLEDBrightness = Math.round(currentLEDBrightness * 10) / 10
                    if(currentLEDBrightness < minLEDBrightness)
                        currentLEDBrightness = minLEDBrightness
                }
            }
        }
    }

    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    Rectangle{
        id: saveButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Save LED Offset")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                connection.receiveFromQmlSetLedOffset(currentLEDBrightness)
                stackView.pop(StackView.Immediate)
            }
        }
    }
    Connections{
        target: connection
        onSendToQmlLEDOffset:{
            currentLEDBrightness = offset
        }
    }
    Component.onCompleted: {
        connection.receiveFromQmlGetLedOffset()
    }
}
