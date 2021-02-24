import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    width: 480
    height: 320

    enum BTNCalibration {
        FirstPlus,
        FirstMinus,
        SecondPlus,
        SecondMinus
    }
    signal calibrationBTNClicked(var value)

    property alias title: titleText.text
    property alias text: calibrationText.text
    property double firstCalibrationValue: 0
    property double secondCalibrationValue: 0
    property double calibrationValue: 0
    property bool buttonEnabled: true

    Text {
        id: titleText

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle{
        width: calibrationText.contentWidth
        height: calibrationText.contentHeight + hightNumber.contentHeight + 30

        anchors.left: parent.left
        anchors.leftMargin: (240 - width) / 2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -20


        color: "#00000000"

        Text {
            id: calibrationText

            color: "#666666"
            font.pixelSize: 20
            font.family: openSansRegular.name

        }
        Text {
            id: hightNumber

            anchors.top: calibrationText.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: calibrationText.horizontalCenter
            text: calibrationValue
            color: "#474747"
            font.pixelSize: 30
            font.family: openSansSemibold.name
        }
    }
    Rectangle{
        id: oneCalibrationButtons

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
            enabled: buttonEnabled

            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/arrow-up.png"
            }
            onClicked: {
                calibrationValue += firstCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.FirstPlus)
            }
        }
        Text {
            id: oneText

            anchors.top: onePlusbutton.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: onePlusbutton.horizontalCenter
            text: firstCalibrationValue
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
            enabled: buttonEnabled

            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/arrow-down.png"
            }
            onClicked: {
                calibrationValue -= firstCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.FirstMinus)
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
            enabled: buttonEnabled

            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/arrow-up.png"
            }
            onClicked: {
                calibrationValue += secondCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.SecondPlus)
            }
        }
        Text {
            id: twoText

            anchors.top: twoPlusbutton.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: twoPlusbutton.horizontalCenter
            text: secondCalibrationValue
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
            enabled: buttonEnabled
            Image {
                anchors.centerIn: parent

                scale: 0.5
                source: "qrc:/image/arrow-down.png"
            }
            onClicked: {
                calibrationValue -= secondCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.SecondMinus)
            }
        }
    }
}
