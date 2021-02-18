import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
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
    function open(ssid,bssid){
        setSSID(ssid)
        setBSSID(bssid)
        popup.popupOpen()
    }
    function setSSID(text){
        ssidText.text = text
    }
    function setBSSID(text){
        bssid = text
    }
}
