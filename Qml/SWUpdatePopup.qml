import QtQuick 2.12
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    property var exText: "전원을 제거하지 말고 프린터 종료된 후\r\n1분 뒤 다시 켜주세요."

    body: Rectangle{
        width: Math.max(updateText.width, progressBar.width)
        height: updateText.height + progressBar.height
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
    }
    function autoReboot(){
        exText="업데이트가 종료된 후 자동으로 부팅됩니다.\r\n전원을 제거하지 말아주세요."
    }
}
