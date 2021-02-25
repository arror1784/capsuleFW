import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    property int tryCount: 0
    property int maxTryCount: 5

    signal startPrintingButtonClicked()

    hasBTN: true

    body: Rectangle{
        id: bodyRectangle
        width: Math.max(text.width, countText.width)
        height: text.height + countText.height + 5
        Text {
            id: text
            text: qsTr("Are you sure you want to Factory Reset?")
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }
        Text {
            id:countText
            anchors.top: text.bottom
            anchors.topMargin: 5
            text: tryCount + "/" + maxTryCount
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }
    }
    onOpened: {
        tryCount = 0
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

        text: tryCount >= maxTryCount ? qsTr("Reset") : qsTr("Yes")

        onClicked: {
            tryCount++
            if(tryCount > maxTryCount){
                factory.reset()
            }
        }
    }
}
