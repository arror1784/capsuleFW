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

        isPopup: true

        text: qsTr("close")

        onAcceptClicked: {
            popup.close()
        }
    }
    function setText(text){
        resinText.text = text
    }
}
