import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    body: Text {
        id: wifiText
        text: qsTr("")
        font.family: nanumBarunGothic.name
        font.pixelSize: 20
        color: "#474747"
    }
    acceptBTN: AcceptBTN{
        id: closeButton

        isPopup: true

        text: qsTr("close")

        onAcceptClicked: {
            popup.close()
        }
    }
    function setText(text){
        wifiText.text = text
    }

    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}
