import QtQuick 2.10
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.1

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false
    signal disconnectButtonClicked()

    property string ssid: ""
    property string bssid: ""

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    InputPanel {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: parent.width
        visible:  Qt.inputMethod.visible
        parent: Overlay.overlay
        z: 1
        focus: true
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
        modal: false
        focus: true
        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -22
            Column{
                id: optionText
                Text {
                    text: qsTr("WIFI ssid")
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
                    id: ssidText
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
            id: disconnectButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8

            Text {
                text: qsTr("disconnect")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    disconnectButtonClicked()
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

    function open(ssid,bssid){
        setSSID(ssid)
        setBSSID(bssid)
        popup.open()
    }
    function setSSID(text){
        ssidText.text = text
    }
    function setBSSID(text){
        bssid = text
    }
}
