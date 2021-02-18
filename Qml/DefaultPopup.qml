import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal back()
    signal accept()

    property bool hasBTN: false
    property int addtionalOffset: 0
    property alias body: popupItem.children
    property alias acceptBTN: btnParent.children
    property alias backBTN: btnParent.children

    Popup{
        id: popup
        width: parent.width - 60
        height: parent.height - 60
        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.NoAutoClose

        background: Rectangle{
            id: backgroundPopUp
            anchors.fill: parent
            color: "#FAFDFF"
            radius: 8
        }
        modal: true
        focus: true

        Item{
            id: popupItem

            width: childrenRect.width
            height: childrenRect.height

            anchors.centerIn: parent
            anchors.verticalCenterOffset: 0 + addtionalOffset
        }
        Item{
            id: btnParent
            anchors.fill: parent
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }
    states: [
        State {
            name: "hasBTN"
            when: hasBTN
            PropertyChanges { target: popupItem; anchors.verticalCenterOffset: -20 + addtionalOffset}
        }
    ]
    function popupOpen(){
        popup.open()
    }
    function popupClose(){
        popup.close()
    }
}
