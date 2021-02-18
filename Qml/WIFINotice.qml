import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {
    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }
    FontLoader{
        id: nanumBarunGothic
        source: "qrc:/fonts/NanumBarunGothic.ttf"
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
        modal: true
        focus: true

        Text {
            id: wifiText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("")
            font.family: nanumBarunGothic.name
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
            popupBack.visible = false
        }
    }
    function setText(text){
        wifiText.text = text
    }

    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
}
