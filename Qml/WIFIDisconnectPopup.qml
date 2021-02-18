import QtQuick 2.10
import QtQuick.Controls 2.5

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
        BackBTN{
            id: cancleButton

            isPopup: true

            text: qsTr("Cancel")

            onBackClicked: {
                popup.close()
            }
        }
        AcceptBTN{
            id: disconnectButton

            isPopup: true

            text: qsTr("disconnect")

            onAcceptClicked: {
                disconnectButtonClicked()
                popup.close()
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
