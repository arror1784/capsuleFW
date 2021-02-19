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

        onBtnClicked: {
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

        onBtnClicked: {
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

        onBtnClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/WIFISelectList.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: update

        text: qsTr("Update")

        imgSource: "qrc:/image/update.png"

        imgScale: 0.7

        selectedPosition: MenuBTN.BTNPosition.BottomLeft

        onBtnClicked: {
            stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateMenu.qml"),StackView.Immediate)
        }
    }
    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    IpPopup{
        id: ipPopup
    }
}
