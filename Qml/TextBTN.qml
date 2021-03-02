import QtQuick 2.0

Rectangle{
    id: backButton

    signal clicked()

    property alias text: text.text
    property alias enabled: mouseArea.enabled
    property alias textColor: text.color

    Text {
        id: text
        color: "#666666"
        font.family: openSansSemibold.name
        font.pixelSize: 20

        anchors.centerIn: parent
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            btnClicked()
        }
    }
    function btnClicked(){
        clicked()
    }
}
