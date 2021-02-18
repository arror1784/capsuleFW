import QtQuick 2.12
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    Rectangle{
        width: updateText.width + progressBar.width
        height: updateText.height + progressBar.height
        Text {
            id: updateText
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            text: exText
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
        }
    }
    function open(){
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}

