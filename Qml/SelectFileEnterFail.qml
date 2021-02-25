import QtQuick 2.12
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    property var error: false

    hasBTN: true

    body: Text {
        id: errorText
        text: error ? qsTr("other user control this printer") : ("time out")
        font.family: openSansSemibold.name
        font.pixelSize: 20
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
        errorText.text = text
    }
    function setError(errora){
        error = errora
    }
}
