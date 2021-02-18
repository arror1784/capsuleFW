import QtQuick 2.0

Rectangle{
    id: selectButton

    signal acceptClicked()

    property bool isPopup: false
    property alias text: acceptBTN.text
    property alias enabled: mouseArea.enabled


    width: 215
    height: 40

    color: "#00C6EA"

    radius: 8

    Text {
        id: acceptBTN
        text: qsTr("Accept")
        color: "#FFFFFF"
        font.family: openSansSemibold.name
        font.pixelSize: 20

        anchors.centerIn: parent
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            acceptClicked()
        }
    }
    states: [
        State {
            name: "default"
            when: !isPopup
            PropertyChanges { target: selectButton; width: 215 }
            PropertyChanges { target: selectButton; height: 40 }
            PropertyChanges { target: selectButton; anchors.bottom: parent.bottom }
            PropertyChanges { target: selectButton; anchors.bottomMargin: 10 }
            PropertyChanges { target: selectButton; anchors.right: parent.right }
            PropertyChanges { target: selectButton; anchors.rightMargin: 15 }
        },
        State {
            name: "popup"
            when: isPopup
            PropertyChanges { target: selectButton; width: 185 }
            PropertyChanges { target: selectButton; height: 40 }
            PropertyChanges { target: selectButton; anchors.bottom: parent.bottom }
            PropertyChanges { target: selectButton; anchors.bottomMargin: 10 }
            PropertyChanges { target: selectButton; anchors.right: parent.right }
            PropertyChanges { target: selectButton; anchors.rightMargin: 5 }
        }
    ]
}
