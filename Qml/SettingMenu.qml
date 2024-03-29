import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320
    MenuBTN{
        id: heightCalibration

        text: qsTr("Height")

        imgSource: "qrc:/image/calibration.png"
        imgScale: 0.7

        selectedPosition: MenuBTN.BTNPosition.TopLeft

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/HeightCalibration.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: ledCalibration

        text: qsTr("LED")

        imgSource: "qrc:/image/light.png"

        imgWidth: 67
        imgHeight: 67

        imgScale: 0.95
        imgRotation: 180

        selectedPosition: MenuBTN.BTNPosition.TopRight

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/LEDCalibration.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: firmwareUpdate

        text: qsTr("WiFi")

        imgSource: "qrc:/image/wifi.png"

        imgWidth: 67
        imgHeight: 67

        imgScale: 0.8

        selectedPosition: MenuBTN.BTNPosition.BottomRight

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/WIFISelectList.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: update

        text: qsTr("Update")

        imgSource: "qrc:/image/update.png"

        imgScale: 0.7

        selectedPosition: MenuBTN.BTNPosition.BottomLeft

        onClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateMenu.qml"),StackView.Immediate)
        }
    }
    BackBTN{
        id: backButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        onClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    IpPopup{
        id: ipPopup
    }
}
