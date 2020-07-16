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

    property bool buttonEnbled: false
    property var exText: "will be auto shutdow \r\n"

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
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

        Rectangle{
            width: progressText.width
            height: progressText.height + 30
            anchors.centerIn: parent
            Text {
                id: progressText
                anchors.centerIn: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: exText + "0%"
                font.family: openSansSemibold.name
                font.pixelSize: 20
                color: "#474747"
            }
        }
        Rectangle{
            id: backButton
            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 5

            color: "#DCEAF3"

            radius:  8
            opacity: buttonEnbled ? 1 : 0.7
            Text {
                text: qsTr("back")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                enabled: buttonEnbled
                onClicked: {
                    back()
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
    function setProgress(progress){
        progressText.text = exText + progress +"%"
    }
    function setTest(text){
        progressText.text = text
    }
    function setBTNEnabled(enabled){
        buttonEnbled = enabled
    }
}
