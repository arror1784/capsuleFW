import QtQuick 2.0

MultiBTN{
    id: menuBTN

    enum BTNPosition {
        NONE,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    }

    property int selectedPosition: MenuBTN.BTNPosition.NONE


    radius: 5
    color: "#DCEAF3"

    width: 215
    height: 110

    states: [
        State {
            name: "topLeft"
            when: selectedPosition === MenuBTN.BTNPosition.TopLeft
            PropertyChanges { target: menuBTN; anchors.top: parent.top }
            PropertyChanges { target: menuBTN; anchors.topMargin: 20 }
            PropertyChanges { target: menuBTN; anchors.left: parent.left }
            PropertyChanges { target: menuBTN; anchors.leftMargin: 15 }
        },
        State {
            name: "topRight"
            when: selectedPosition === MenuBTN.BTNPosition.TopRight
            PropertyChanges { target: menuBTN; anchors.top: parent.top }
            PropertyChanges { target: menuBTN; anchors.topMargin: 20 }
            PropertyChanges { target: menuBTN; anchors.right: parent.right }
            PropertyChanges { target: menuBTN; anchors.rightMargin: 15 }
        },
        State {
            name: "bottomLeft"
            when: selectedPosition === MenuBTN.BTNPosition.BottomLeft
            PropertyChanges { target: menuBTN; anchors.bottom: parent.bottom }
            PropertyChanges { target: menuBTN; anchors.bottomMargin: 70 }
            PropertyChanges { target: menuBTN; anchors.left: parent.left }
            PropertyChanges { target: menuBTN; anchors.leftMargin: 15 }
        },
        State {
            name: "bottomRight"
            when: selectedPosition === MenuBTN.BTNPosition.BottomRight
            PropertyChanges { target: menuBTN; anchors.bottom: parent.bottom }
            PropertyChanges { target: menuBTN; anchors.bottomMargin: 70 }
            PropertyChanges { target: menuBTN; anchors.right: parent.right }
            PropertyChanges { target: menuBTN; anchors.rightMargin: 15 }
        }
    ]
}
