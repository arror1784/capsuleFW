import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property string updateMode
    property bool isUpdateModeSelect: true

    Rectangle {
        id: network

        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 15

        Rectangle{
            width: networkText.width
            height: networkImage.height + networkText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: networkImage
                source: "qrc:/image/network.png"

                height: 67
                width: 67

                scale: 0.57

                anchors.horizontalCenter: networkText.horizontalCenter
            }

            Text {
                id: networkText
                text: qsTr("Network")
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
                updateMode = "network"
                var it = stackView.find(function(item,index){return item.isUpdateMenu})

                if(it !== null){
                    if(it.updateTarget === "resin"){
                        stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
                    }else{
                        stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdate.qml"),StackView.Immediate)
                    }
                }
            }
        }
    }
    Rectangle {
        id: usb

        width: 215
        height: 110

        color: "#dceaf3"

        radius: 8

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 15

        Rectangle{
            width: usbText.width
            height: usbImage.height + usbText.height
            anchors.centerIn: parent
            color: "#00000000"
            Image {
                id: usbImage
                source: "qrc:/image/USB.png"

                height: 67
                sourceSize.height: 67
                sourceSize.width: 67
                width: 67

                scale: 0.85

                anchors.horizontalCenter: usbText.horizontalCenter
            }

            Text {
                id: usbText
                text: qsTr("USB")
                color: "#666666"

                anchors.top: usbImage.bottom

                font.family: openSansSemibold.name
                font.pixelSize: 20
                font.bold: true
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                updateMode = "usb"

                var it = stackView.find(function(item,index){return item.isUpdateMenu})

                if(it !== null){
                    if(it.updateTarget === "resin"){
                        stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdateSelectFile.qml"),StackView.Immediate)
                    }else{
                        stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdateSelectFile.qml"),StackView.Immediate)
                    }
                }
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
