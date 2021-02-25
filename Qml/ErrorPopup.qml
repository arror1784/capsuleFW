import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()

    hasBTN: true

    body: Text {
        id: errorText

        text: qsTr("print setting error")

        font.family: nanumBarunGothic.name
        font.pixelSize: 20

        color: "#474747"
    }

    BackBTN{
        id: backButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5
        
        onClicked: {
            back()
            close()
        }
    }

    function openPopup(code){
        if(code === 1){
            errorText.text = "Error: LCD가 빠졌습니다\nLCD를 다시 넣고 재부팅해주세요."
        }else if(code === 2){
            errorText.text = "Error: 파일에 문제가 있습니다."
        }else if(code === 3){
            errorText.text = "Error: 세팅값에 문제가 있습니다."
        }else if(code === 4){
            errorText.text = "Error: 이미 프린트 중입니다."
        }else if(code === 5){
            errorText.text = "Error: USB 케이블이 연결되지 않았습니다."
        }else if(code === 6){
            errorText.text = "Error: 파일에 문제가 있습니다."
        }else if(code === 7){
            errorText.text = "출력완료 후 확인이 필요합니다.\n제품에서 close버튼을 눌러주세요."
        }else if(code === 8){
            errorText.text = "Error: 지원하지 않는 layer height입니다."
        }else{
            errorText.text = "Error: 오류가 발생했습니다."
        }

        popup.open()
    }
}
