import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal back()
    signal sendToShutdown()

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

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("Are you sure you want to exit?")
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }
        BackBTN{
            id: backButton

            isPopup: true

            onBackClicked: {
                back()
                close()
            }
        }
        AcceptBTN{
            id: exitButton

            isPopup: true

            text: qsTr("exit")

            onAcceptClicked: {
                sendToShutdown()
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
    function close(){
        popup.close()
    }
}
