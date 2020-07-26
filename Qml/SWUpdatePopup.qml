import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal cancel()
    signal swUpdate()

    property bool cancelButtonEnbled: false
    property bool updateButtonEnbled: false
    property bool updateProgressEnbled: false

    property var exText: "전원을 제거하지 말고 프린터 종료된 후\r\n1분 뒤 다시 켜주세요."

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
            id: updateText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("SW update check")
            font.family: openSansRegular.name
            font.pixelSize: 20

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            color: "#474747"
        }
        ProgressBar {
            id: progressBar

            anchors.top: updateText.bottom
            anchors.horizontalCenter: updateText.horizontalCenter
            indeterminate: true

            visible: updateProgressEnbled
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

                    updateText.text = "Updating SW\r\n" + exText

                    updateProgressEnbled = true
                    cancelButtonEnbled = false
                    updateButtonEnbled = false

                    swUpdate()
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
        updateButtonEnbled = false
        updateProgressEnbled = false

        updateText.text = "SW update not available"
    }
    function updateAvailable(){
        cancelButtonEnbled = true
        updateButtonEnbled = true

        updateText.text = "SW update available"
    }
    function updateFinished(){
        cancelButtonEnbled = true
        updateProgressEnbled = false

        updateText.text = "SW update finished"
    }
    function updateError(){
        cancelButtonEnbled = true
        updateProgressEnbled = false

        updateText.text = "SW update error"
    }
}
