import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    body: Rectangle{
        width: optionText.width + valueText.width + 15
        height: optionText.height
        Column{
            id: optionText
            Text {
                text: qsTr("File name")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("Material")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("Layer height")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
        }
        Column{
            id: valueText
            anchors.left: optionText.right
            anchors.leftMargin: 15
            Text {
                id: fileNameText
                text: qsTr("lower.stl")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 200
                elide: Text.ElideRight
            }
            Text {
                id: materialText
                text: qsTr("Temporary")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 200
                elide: Text.ElideRight
            }
            Text {
                id: layerHeightText
                text: qsTr("layer height")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 200
                elide: Text.ElideRight
            }
        }
    }
    backBTN: BackBTN{
        id: cancleButton

        isPopup: true

        text: qsTr("Cancel")

        onBackClicked: {
            popup.close()
        }
    }
    acceptBTN: AcceptBTN{
        id: startButton

        isPopup: true

        text: qsTr("Start printing")

        onAcceptClicked: {
            startPrintingButtonClicked()
            popup.close()
        }
    }
    function open(){
        popup.popupOpen()
    }
    function setText(fileName, material, layerHeight){
        fileNameText.text = fileName
        materialText.text = material
        layerHeightText.text = Math.round(layerHeight * 1000) / 1000 + "mm/layer"
    }
}
