import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false
    signal startPrintingButtonClicked()

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    Popup{
        id: popup
        width: parent.width - 60
        height: parent.height - 60
        anchors.centerIn: Overlay.overlay

        background: Rectangle{
            id: backgroundPopUp
            anchors.fill: parent
            color: "#FAFDFF"
            radius: 8
        }
        modal: true
        focus: true
        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
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

        Rectangle{
            id: cancleButton
            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "#DCEAF3"

            radius: 8

            Text {
                text: qsTr("Cancel")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    popup.close()
                }
            }
        }
        Rectangle{
            id: startButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8

            Text {
                text: qsTr("Start printing")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    startPrintingButtonClicked()
                    popup.close()
                }
            }
        }

        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }
    function open(){
        popup.open()
    }
    function setText(fileName, material, layerHeight){
        fileNameText.text = fileName
        materialText.text = material
        layerHeightText.text = Math.round(layerHeight * 1000) / 1000 + "mm/layer"
    }
}
