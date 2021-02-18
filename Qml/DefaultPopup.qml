import QtQuick 2.10
import QtQuick.Controls 2.5

Popup{
    id: popup

    width: 420
    height: 260

//    color: "#BDBDBD"
//    opacity: 0.7

    signal back()
    signal accept()

    property bool hasBTN: false
    property int addtionalOffset: 0
    property alias body: popupItem.children

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.NoAutoClose

    background: Rectangle{
        id: backgroundPopUp
        anchors.fill: parent
        color: "#FAFDFF"
        radius: 8
    }
    modal: true
    Overlay.modal: Rectangle {
        color: "#BDBDBD"
        opacity: 0.7
    }
    focus: true

    Item{
        id: popupItem

        width: childrenRect.width
        height: childrenRect.height

        anchors.centerIn: parent
        anchors.verticalCenterOffset: hasBTN ? -20 + addtionalOffset : 0 + addtionalOffset
    }
}
