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

        text: qsTr("close")

        onAcceptClicked: {
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
