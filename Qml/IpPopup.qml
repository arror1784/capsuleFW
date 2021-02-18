import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false
    property var ipList: []

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
        focus: true

        Text {
            id: ipText
            anchors.centerIn: parent
            text: qsTr("")
            font.family: openSansSemibold.name
            font.pixelSize: 20
            color: "#474747"
        }
        AcceptBTN{
            id: closeButton

            isPopup: true

            text: qsTr("close")

            onAcceptClicked: {
                popup.close()
            }
        }
        onOpened: {
            popupBack.visible = true
        }
        onClosed: {
            popupBack.visible = false
        }
    }
    Connections{
        id: networkConnection
        target: nc
    }
    function open(){
        nc.updateIpAddressList()
        ipList = nc.getIpAddressList()
        var iptext = ""
        for (var i = 0; i < ipList.length; i++){
            iptext += ipList[i] + ":5000\n"
        }
        ipText.text = iptext

        popup.open()
    }
    function close(){
        popup.close()
    }
}
