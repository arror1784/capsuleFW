import QtQuick 2.0
import QtQuick.Controls 2.5
DefaultPopup{
    id: popup

    signal printStop()
    signal printResume()

    property bool buttonEnbled: false

    hasBTN: true

    body: Text {
        text: qsTr("Are you sure you want to quit printing")
        font.family: openSansRegular.name
        font.pixelSize: 20
        color: "#474747"
    }
    BackBTN{
        id: resumeButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5

        opacity: buttonEnbled ? 1 : 0.7
        enabled: buttonEnbled

        text: qsTr("Resume")

        onClicked: {
            printResume()
        }
    }
    AcceptBTN{
        id: quitButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        opacity: buttonEnbled ? 1 : 0.5
        enabled: buttonEnbled

        text: qsTr("Quit")

        onClicked: {
            buttonEnbled = false
            printStop()
        }
    }
    function setButtonEnabled(aa){
        buttonEnbled = aa
    }
}
