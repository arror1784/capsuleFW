import QtQuick 2.12
import QtQuick.Controls 2.12

DefaultPopup{
    id: popup

    body: Text {
        text: qsTr("연결중입니다....")
        font.family: nanumBarunGothic.name
        font.pixelSize: 20
        color: "#474747"
    }
}
