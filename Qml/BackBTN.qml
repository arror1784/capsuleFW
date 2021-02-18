import QtQuick 2.0


Rectangle{
    id: backButton

    signal backClicked()

    property bool isPopup: false
    property alias text: backText.text
    property alias opacity: backButton.opacity
    property alias enabled: mouseArea.enabled

    width: 215
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
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            backClicked()
        }
    }

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10
    anchors.left: parent.left
    anchors.leftMargin: 5

    states: [
        State {
            name: "default"
            when: !isPopup
            PropertyChanges { target: backButton; width: 215 }
            PropertyChanges { target: backButton; height: 40 }
            PropertyChanges { target: backButton; anchors.bottom: parent.bottom }
            PropertyChanges { target: backButton; anchors.bottomMargin: 10 }
            PropertyChanges { target: backButton; anchors.left: parent.left }
            PropertyChanges { target: backButton; anchors.leftMargin: 15 }
        },
        State {
            name: "popup"
            when: isPopup
            PropertyChanges { target: backButton; width: 185 }
            PropertyChanges { target: backButton; height: 40 }
            PropertyChanges { target: backButton; anchors.bottom: parent.bottom }
            PropertyChanges { target: backButton; anchors.bottomMargin: 10 }
            PropertyChanges { target: backButton; anchors.left: parent.left }
            PropertyChanges { target: backButton; anchors.leftMargin: 5 }
        }
    ]
}
