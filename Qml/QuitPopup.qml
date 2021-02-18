import QtQuick 2.0
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

    signal printStop()
    signal printResume()

    property bool buttonEnbled: false

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
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: qsTr("Are you sure you want to quit printing")
            font.family: openSansRegular.name
            font.pixelSize: 20
            color: "#474747"
        }

        Rectangle{
            id: resumeButton
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
                text: qsTr("Resume")
                color: "#666666"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                enabled: buttonEnbled
                onClicked: {
                   popupBack.printResume()
                }
            }
        }
        AcceptBTN{
            id: quitButton

            isPopup: true
            opacity: buttonEnbled ? 1 : 0.5
            enabled: buttonEnbled

            text: qsTr("Quit")

            onAcceptClicked: {
                buttonEnbled = false
                printStop()
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
    function setButtonEnabled(aa){
        buttonEnbled = aa
    }
}
