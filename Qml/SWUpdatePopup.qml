import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    property var exText: "전원을 제거하지 말고 프린터 종료된 후\r\n1분 뒤 다시 켜주세요."

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

        closePolicy: Popup.NoAutoClose

        Text {
            id: updateText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: exText
            font.family: nanumBarunGothic.name
            font.pixelSize: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            color: "#474747"
        }
        ProgressBar {
            id: progressBar

            anchors.top: updateText.bottom
            anchors.horizontalCenter: updateText.horizontalCenter
            indeterminate: true
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }
    function autoReboot(){
        exText="업데이트가 종료된 후 자동으로 부팅됩니다.\r\n전원을 제거하지 말아주세요."
    }

    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
}
