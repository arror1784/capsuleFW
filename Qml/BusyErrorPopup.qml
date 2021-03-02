import QtQuick 2.0
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    signal back()

    hasBTN: true

    body: Text {
        text: qsTr("you can exit on main menu")
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
}
