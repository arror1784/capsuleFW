import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    body: Text {
        text: qsTr("Are you sure you want to exit?")
        font.family: openSansRegular.name
        font.pixelSize: 20
        color: "#474747"
    }
    backBTN: BackBTN{
        id: backButton

        isPopup: true

        onBackClicked: {
            back()
            close()
        }
    }
    acceptBTN: AcceptBTN{
        id: exitButton

        isPopup: true

        text: qsTr("exit")

        onAcceptClicked: {
            sendToShutdown()
        }
    }
    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}
