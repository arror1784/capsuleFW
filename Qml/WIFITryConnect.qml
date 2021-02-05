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
            text: qsTr("연결중입니다....")
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
            color: "#474747"
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
