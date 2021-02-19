import QtQuick 2.0

Rectangle{
    id: enumBTN

    enum BTNPosition {
        NONE,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    }

    signal btnClicked()

    property int selectedPosition: MenuBTN.BTNPosition.NONE

    property alias text: menuText.text
    property alias font: menuText.font
    property alias fontColor: menuText.color


    property alias imgSource: iconImage.source
    property alias imgScale: iconImage.scale
    property alias imgRotation: iconImage.rotation
    property alias imgWidth: iconImage.width
    property alias imgHeight: iconImage.height
    property alias imgSourceWidth: iconImage.sourceSize.width
    property alias imgSourceHeight: iconImage.sourceSize.height

    radius: 5
    color: "#DCEAF3"

    width: 215
    height: 110

    Rectangle{
        width: iconImage.width
        height: iconImage.height + menuText.height

        anchors.centerIn: parent

        color: "#00000000"
        Image {
            id: iconImage

            antialiasing: true
            smooth: true
        }
        Text {
            id: menuText
            color: "#666666"
            anchors.top: iconImage.bottom
            anchors.horizontalCenter: iconImage.horizontalCenter

            font.family: openSansSemibold.name
            font.pixelSize: 20
            font.bold: true
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            btnClicked()
        }
    }
    states: [/*
        State {
            name: "none"
            when: selectedPosition === MenuBTN.BTNPosition.NONE
        },*/
        State {
            name: "topLeft"
            when: selectedPosition === MenuBTN.BTNPosition.TopLeft
            PropertyChanges { target: enumBTN; anchors.top: parent.top }
            PropertyChanges { target: enumBTN; anchors.topMargin: 20 }
            PropertyChanges { target: enumBTN; anchors.left: parent.left }
            PropertyChanges { target: enumBTN; anchors.leftMargin: 15 }
        },
        State {
            name: "topRight"
            when: selectedPosition === MenuBTN.BTNPosition.TopRight
            PropertyChanges { target: enumBTN; anchors.top: parent.top }
            PropertyChanges { target: enumBTN; anchors.topMargin: 20 }
            PropertyChanges { target: enumBTN; anchors.right: parent.right }
            PropertyChanges { target: enumBTN; anchors.rightMargin: 15 }
        },
        State {
            name: "bottomLeft"
            when: selectedPosition === MenuBTN.BTNPosition.BottomLeft
            PropertyChanges { target: enumBTN; anchors.bottom: parent.bottom }
            PropertyChanges { target: enumBTN; anchors.bottomMargin: 70 }
            PropertyChanges { target: enumBTN; anchors.left: parent.left }
            PropertyChanges { target: enumBTN; anchors.leftMargin: 15 }
        },
        State {
            name: "bottomRight"
            when: selectedPosition === MenuBTN.BTNPosition.BottomRight
            PropertyChanges { target: enumBTN; anchors.bottom: parent.bottom }
            PropertyChanges { target: enumBTN; anchors.bottomMargin: 70 }
            PropertyChanges { target: enumBTN; anchors.right: parent.right }
            PropertyChanges { target: enumBTN; anchors.rightMargin: 15 }
        }
    ]
}
