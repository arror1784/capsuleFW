import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    Text {
        id: usbText
        text: "USB가 없습니다"

        font.family: openSansSemibold.name
        font.pixelSize: 20
        color: "#474747"
    }
    AcceptBTN{
        id: closeButton

        isPopup: true

        text: qsTr("close")

        onAcceptClicked: {
            popup.close()
            back()
        }
    }
    function setText(text){
        resinText.text = text
    }

    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}

