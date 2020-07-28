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
            text: error ? qsTr("other user control this printer") : ("time out")
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
                onClicked: popup.close()
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
