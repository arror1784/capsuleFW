import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()
    signal sendToShutdown()

    hasBTN: true

    body: Text {
        text: qsTr("Are you sure you want to exit?")
        font.family: openSansRegular.name
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
    AcceptBTN{
        id: exitButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        text: qsTr("exit")

        onClicked: {
            sendToShutdown()
        }
    }
}
