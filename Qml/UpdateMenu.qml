import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    id: element
    width: 480
    height: 320

    property string updateTarget
    property bool isUpdateMenu: true

    MenuBTN{
        id: resinUpdate

        text: qsTr("Resin Update")

        imgSource: "qrc:/image/fill.png"
        imgWidth: 67
        imgHeight: 67
        imgScale: 0.9

        selectedPosition: MenuBTN.BTNPosition.TopLeft

        onBtnClicked: {
            updateTarget = "resin"
//                stackView.push(Qt.resolvedUrl("qrc:/Qml/ResinUpdate.qml"),StackView.Immediate)
            stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateModeSelect.qml"),StackView.Immediate)
        }
    }
    MenuBTN{
        id: softwareUpdate

        text: qsTr("Software Update")

        imgSource: "qrc:/image/download.png"
        imgWidth: 67
        imgHeight: 67
        imgScale: 0.8

        selectedPosition: MenuBTN.BTNPosition.TopRight

        onBtnClicked: {
            updateTarget = "software"
//                stackView.push(Qt.resolvedUrl("qrc:/Qml/SWUpdate.qml"),StackView.Immediate)
            stackView.push(Qt.resolvedUrl("qrc:/Qml/UpdateModeSelect.qml"),StackView.Immediate)
        }
    }
    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)

        }
    }
}
