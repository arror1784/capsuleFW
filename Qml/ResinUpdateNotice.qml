import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    body: Text {
        id: resinText
        text: qsTr("Resin Update Finished")
        font.family: openSansSemibold.name
        font.pixelSize: 20
        anchors.verticalCenterOffset: -20
        color: "#474747"
    }
    AcceptBTN{
        id: closeButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        text: qsTr("close")

        onClicked: {
            popup.close()
        }
    }
    function setText(text){
        resinText.text = text
    }
}
