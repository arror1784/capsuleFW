import QtQuick 2.12
import QtQuick.Controls 2.12

DefaultPopup{
    id: popup

    hasBTN: true

    body: Text {
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
}
