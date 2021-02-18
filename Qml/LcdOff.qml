import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal printStop()
    signal printResume()

    property bool buttonEnbled: false

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
        focus: true

        Text {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("Error: LCD가 빠졌습니다\nLCD를 다시 넣고 재부팅해주세요")
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
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
    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
}
