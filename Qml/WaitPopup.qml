import QtQuick 2.12
import QtQuick.Controls 2.12

DefaultPopup{
    id: popup

    Text {
        text: qsTr("waiting for movement")
        font.family: openSansSemibold.name
        font.pixelSize: 20
        color: "#474747"
    }

    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}
