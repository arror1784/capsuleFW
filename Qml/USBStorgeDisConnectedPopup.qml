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

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

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
            text: "USB가 없습니다"

            font.family: openSansSemibold.name
            font.pixelSize: 20
            color: "#474747"
        }

        Rectangle{
            id: closeButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8

            Text {
                text: qsTr("close")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    popup.close()
                    back()
                }
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

