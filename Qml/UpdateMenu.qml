import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property string updateTarget
    property bool isUpdateMenu: true

    Rectangle{
        id: resinUpdate
        radius: 5

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        width: 215
        height: 110

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
                updateTarget = "resin"
//                stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
                stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateModeSelect.qml"),StackView.Immediate)
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
            onClicked: {
                updateTarget = "software"
//                stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdate.qml"),StackView.Immediate)
                stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateModeSelect.qml"),StackView.Immediate)

            }
        }
    }
    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)

        }
    }
}
