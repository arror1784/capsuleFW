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
        id: resinUpdate
        radius: 5
        anchors.top: parent.top
        anchors.topMargin: 20
        color: "#DCEAF3"

        width: 215
        height: 110

        anchors.left: parent.left
        anchors.leftMargin: 15

        Rectangle{
            width: resinUpdateText.width
            height: resinUpdateImage.height + resinUpdateText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: resinUpdateImage
                source: "qrc:/image/fill.png"

                height: 67
                width: 67

                scale: 0.9
                anchors.horizontalCenter: resinUpdateText.horizontalCenter
            }

            Text {
                id: resinUpdateText
                text: qsTr("Resin Update")
                color: "#666666"

                anchors.top: resinUpdateImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
            }
        }
    }
    Rectangle {
        id: softwareUpdate
        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 15
        Rectangle{
            width: firmwareUpdateText.width
            height: firmwareUpdateImage.height + firmwareUpdateText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: firmwareUpdateImage

                width: 67
                height: 67

                source: "qrc:/image/download.png"

                scale: 0.8
                anchors.horizontalCenter: firmwareUpdateText.horizontalCenter
            }

            Text {
                id: firmwareUpdateText
                text: qsTr("Software Update")
                color: "#666666"

                anchors.top: firmwareUpdateImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {11
                stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdate.qml"),StackView.Immediate)
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
}
