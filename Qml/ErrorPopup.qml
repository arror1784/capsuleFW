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
        modal: true
        focus: true

        Text {
            id: errorText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("print setting error")
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }

        Rectangle{
            id: backButton
            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "#DCEAF3"

            radius:  8

            Text {
                text: qsTr("Back")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    back()
                    close()
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
    function open(code){
        if(code === 1){
            errorText.text = "Error: LCD가 빠졌습니다"
        }else if(code === 2){
            errorText.text = "Error: 파일에 문제가 있습니다"
        }else if(code === 3){
            errorText.text = "Error: 세팅값에 문제가 있습니다"
        }else if(code === 4){
            errorText.text = "Error: 이미 프린트 중입니다"
        }else if(code === 5){
            errorText.text = "Error: USB 케이블이 연결되지 않았습니다"
        }else if(code === 6){
            errorText.text = "Error: 파일에 문제가 있습니다"
        }else{
            errorText.text = "Error: 오류가 발생했습니다"
        }

        popup.open()
    }
    function close(){
        popup.close()
    }
}
