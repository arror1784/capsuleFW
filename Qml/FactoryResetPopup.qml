import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    property int tryCount: 0
    property int maxTryCount: 1

    property string resetText: ""

    signal startPrintingButtonClicked()

    hasBTN: true

    body: Rectangle{
        id: bodyRectangle
        width: Math.max(text.width,info1.width,info2.width,info3.width)
        height: text.height + info1.height + info2.height + info3.height + 25
        Text {
            id: text
            text: resetText
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
            font.bold: true
            color: "#474747"
        }
        Text {
            id: info1
            anchors.top: text.bottom
            anchors.topMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("공장 초기화 진행시 제품이 다시 ")
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
            color: "#474747"
        }
        Text {
            id: info2
            anchors.top: info1.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("켜질때까지 전원을 제거하지 말아주세요.")
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
            color: "#474747"
        }
        Text {
            id: info3
            anchors.top: info2.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("전원 제거시 문제가 발생할 수 있습니다.")
            font.family: nanumBarunGothic.name
            font.pixelSize: 20
            color: "#474747"
        }
    }
    onOpened: {
        tryCount = 0
        resetText = qsTr("공장 초기화를 진행하시겠습니까?")
    }

    BackBTN{
        id: cancleButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5

        text: qsTr("Cancel")

        onClicked: {
            popup.close()
        }
    }
    AcceptBTN{
        id: startButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        text: tryCount === maxTryCount ? qsTr("Reset") : qsTr("Yes")

        onClicked: {
            tryCount++
            if(tryCount === maxTryCount){
                resetText = qsTr("정말로 공장 초기화를 진행하시겠습니까?")
            }else if(tryCount > maxTryCount){
                factory.reset()
            }
        }
    }
}
