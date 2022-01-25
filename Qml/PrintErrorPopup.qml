import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()

    hasBTN: true

    body: Text {
        id: errorText

        text: qsTr("print error")

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
            errorText.text = "Error: 이미지 순서 문제가 생겼습니다.\n새로운 파일로 출력 시도 바랍니다."
        }else if(code === 2){
            errorText.text = "Error: LCD가 빠졌습니다.\nLCD 연결을 확인주세요."
        }else if(code === 3){
            errorText.text = "Error: 파일에 문제가 생겼습니다.\n새로운 파일로 출력 시도 바랍니다."
        }else if(code === 4){
            errorText.text = "Error: 비정상 창 발생 오류가 발생했습니다.\n재출력 시도 바랍니다."
        }else{
            errorText.text = "Error: 오류가 발생했습니다."
        }


        popup.open()
    }
}
