import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal cancel()
    signal resinUpdate()

    property bool cancelButtonEnbled: false
    property bool updateButtonEnbled: false

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

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

        closePolicy: Popup.NoAutoClose

        Text {
            id: text
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("update check")
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }

        Rectangle{
            id: cancelButton
            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "#DCEAF3"

            radius:  8
            opacity: cancelButtonEnbled ? 1 : 0.7
            Text {
                text: qsTr("cancel")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                enabled: cancelButtonEnbled
                onClicked: {
                   cancel()
                }
            }
        }
        Rectangle{
            id: updateButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8
            opacity: updateButtonEnbled ? 1 : 0.5
            Text {
                text: qsTr("update")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                enabled: updateButtonEnbled
                onClicked: {
                    resinUpdate()

                    cancelButtonEnbled = false
                    updateButtonEnbled = false
                }
            }
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }
    function open(){
        popup.open()
    }
    function close(){
        popup.close()
    }
    function updateNotAvailable(){
        cancelButtonEnbled = true
        text.text = "update not available"
    }
    function updateAvailable(){
        cancelButtonEnbled = true
        updateButtonEnbled = true

        text.text = "update available"
    }
    function updateFinished(){
        cancelButtonEnbled = true

        text.text = "update finished"
    }
}
