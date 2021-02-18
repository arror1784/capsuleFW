import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    property var error: false

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
        focus: true

        Text {
            id: errorText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: error ? qsTr("other user control this printer") : ("time out")
            font.family: openSansSemibold.name
            font.pixelSize: 20
            color: "#474747"
        }
        AcceptBTN{
            id: closeButton

            text: qsTr("close")

            onAcceptClicked: {
                popup.close()
            }
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            error = false
            popupBack.visible = false
        }
    }
    function setText(text){
        errorText.text = text
    }
    function setError(errora){
        error = errora
    }

    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
}
