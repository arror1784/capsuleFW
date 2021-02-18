import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {
    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

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
            id: resinText
            anchors.centerIn: parent
            text: qsTr("Resin Update Finished")
            font.family: openSansSemibold.name
            font.pixelSize: 20
            anchors.verticalCenterOffset: -20
            color: "#474747"
        }
        AcceptBTN{
            id: closeButton

            isPopup: true

            text: qsTr("close")

            onAcceptClicked: {
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
    function setText(text){
        resinText.text = text
    }

    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
}
