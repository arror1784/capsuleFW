import QtQuick 2.0


Rectangle{
    id: backButton

    signal backClicked()

    property alias text: backText.text

    width: 185
    height: 40

    color: "#DCEAF3"

    radius:  8

    Text {
        id: backText
        text: qsTr("Back")
        color: "#666666"
        font.family: openSansSemibold.name
        font.pixelSize: 20

        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            backClicked()
        }
    }
}
