import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    Rectangle{
        id: heightCalibration
        radius: 5
        anchors.top: parent.top
        anchors.topMargin: 20
        color: "#DCEAF3"

        width: 215
        height: 110

        anchors.left: parent.left
        anchors.leftMargin: 15

        Rectangle{
            width: heightCalibrationText.width
            height: heightCalibrationImage.height + heightCalibrationText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: heightCalibrationImage
                source: "qrc:/image/calibration.png"

                scale: 0.7
                anchors.horizontalCenter: heightCalibrationText.horizontalCenter
            }

            Text {
                id: heightCalibrationText
                text: qsTr("height")
                color: "#666666"

                anchors.top: heightCalibrationImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.push(Qt.resolvedUrl("qrc:/Qml/HeightCalibration.qml"),StackView.Immediate)
            }
        }
    }
    Rectangle {
        id: ledCalibration
        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 15
        Rectangle{
            width: ledCalibrationText.width
            height: ledCalibrationImage.height + ledCalibrationText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: ledCalibrationImage

                width: 67
                height: 67

                rotation: 180

                source: "qrc:/image/light.png"

                scale: 0.95
                anchors.horizontalCenter: ledCalibrationText.horizontalCenter
            }

            Text {
                id: ledCalibrationText
                text: qsTr("LED")
                color: "#666666"

                anchors.top: ledCalibrationImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.push(Qt.resolvedUrl("qrc:/Qml/LEDCalibration.qml"),StackView.Immediate)
            }
        }
    }
    Rectangle {
        id: network

        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.bottom: backButton.top
        anchors.bottomMargin: 15
        anchors.leftMargin: 15
        anchors.left: parent.left
        Rectangle{
            width: networkText.width
            height: networkImage.height + networkText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: networkImage
                source: "qrc:/image/calibration.png"

                scale: 0.7
                anchors.horizontalCenter: networkText.horizontalCenter
            }

            Text {
                id: networkText
                text: qsTr("network")
                color: "#666666"

                anchors.top: networkImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                ipPopup.open()
            }
        }
    }
    Rectangle {
        id: info

        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8
        anchors.verticalCenter: network.verticalCenter

        anchors.right: parent.right
        anchors.rightMargin: 15
        Rectangle{
            width: infoText.width
            height: infoImage.height + infoText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: infoImage
                source: "qrc:/image/calibration.png"

                scale: 0.7
                anchors.horizontalCenter: infoText.horizontalCenter
            }

            Text {
                id: infoText
                text: qsTr("info")
                color: "#666666"

                anchors.top: infoImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
            }
        }
    }
    Rectangle{
        id: backButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Back")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            antialiasing: false
            anchors.leftMargin: 0
            anchors.fill: parent
            onClicked: {
                stackView.pop(StackView.Immediate)
            }
        }
    }
    IpPopup{
        id: ipPopup
    }
}







/*##^## Designer {
    D{i:3;anchors_y:16}D{i:23;anchors_height:112;anchors_width:215;anchors_x:250;anchors_y:16}
}
 ##^##*/
