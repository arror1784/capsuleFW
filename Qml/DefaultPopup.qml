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


    Popup{
        id: popup
        width: parent.width - 60
        height: parent.height - 60
        anchors.centerIn: Overlay.overlay

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
            anchors.verticalCenterOffset: 0
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
            name: "default"
            when: hasBTN
            PropertyChanges { target: popupItem; anchors.verticalCenterOffset: -40 + addtionalOffset }
        }
    ]
    function popupOpen(){
        popup.open()
    }
    function popupClose(){
        popup.close()
    }
}
