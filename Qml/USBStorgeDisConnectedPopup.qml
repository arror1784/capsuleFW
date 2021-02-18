import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {
    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal back()

    Popup{
        id: popup
        width: parent.width - 60
        height: parent.height - 60
        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose

        background: Rectangle{
            id: backgroundPopUp
            anchors.fill: parent
            color: "#FAFDFF"
            radius: 8
        }
        modal: true
        focus: true

        Text {
            id: usbText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
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

