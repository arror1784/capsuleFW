import QtQuick 2.0
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
                text: qsTr("Printing time")
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
                id: printingTimeText
                text: qsTr("15min")
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
    AcceptBTN{
        id: closeButton

        isPopup: true

        text: qsTr("close")

        onAcceptClicked: {
            popup.close()
        }
    }
    function setFilename(fileName){
        fileNameText.text = fileName
    }
    function setPrintingTime(time){
        printingTimeText.text = time
    }
    function setMaterial(material){
        materialText.text = material
    }
    function setLayerHeight(height){
        layerHeightText.text = Math.round(height * 1000) / 1000 + "mm/layer"
    }
}
