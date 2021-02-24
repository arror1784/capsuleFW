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
        CalibrationBTN{
            id: onePlusbutton

            enabled: buttonEnabled
            state: "up"

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
        CalibrationBTN{
            id: oneMinbutton

            anchors.top: oneText.bottom
            anchors.topMargin: 5

            enabled: buttonEnabled
            state: "down"

            onClicked: {
                calibrationValue -= firstCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.FirstMinus)
            }
        }
        CalibrationBTN{
            id: twoPlusbutton

            anchors.left: onePlusbutton.right
            anchors.leftMargin: oneText.contentHeight + 10

            enabled: buttonEnabled
            state: "up"

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
        CalibrationBTN{
            id: twoMinbutton

            anchors.top: twoText.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: twoText.horizontalCenter

            enabled: buttonEnabled
            state: "down"

            onClicked: {
                calibrationValue -= secondCalibrationValue
                calibrationBTNClicked(DefaultCalibration.BTNCalibration.SecondMinus)
            }
        }
    }
}
