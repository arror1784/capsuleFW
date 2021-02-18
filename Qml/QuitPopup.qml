import QtQuick 2.0
import QtQuick.Controls 2.5
DefaultPopup{
    id: popup

    hasBTN: true

    body: Text {
        text: qsTr("Are you sure you want to quit printing")
        font.family: openSansRegular.name
        font.pixelSize: 20
        color: "#474747"
    }
    backBTN: BackBTN{
        id: resumeButton

        isPopup: true
        opacity: buttonEnbled ? 1 : 0.7
        enabled: buttonEnbled

        text: qsTr("Resume")

        onBackClicked: {
            popupBack.printResume()
        }
    }
    acceptBTN: AcceptBTN{
        id: quitButton

        isPopup: true
        opacity: buttonEnbled ? 1 : 0.5
        enabled: buttonEnbled

        text: qsTr("Quit")

        onAcceptClicked: {
            buttonEnbled = false
            printStop()
        }
    }
    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
    function setButtonEnabled(aa){
        buttonEnbled = aa
    }
}
