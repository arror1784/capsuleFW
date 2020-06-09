import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false
    property var ipList: []
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
        focus: true

        Text {
            id: ipText
            anchors.centerIn: parent
            text: qsTr("")
            font.family: openSansSemibold.name
            font.pixelSize: 20
            color: "#474747"
        }
        Rectangle{
            id: startButton

            width: 185
            height: 40

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 5

            color: "#00C6EA"

            radius: 8

            Text {
                text: qsTr("close")
                color: "#FFFFFF"
                font.family: openSansSemibold.name
                font.pixelSize: 20

                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: popup.close()
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
            iptext += ipList[i] + "\n"
        }
        ipText.text = iptext

        popup.open()
    }
    function close(){
        popup.close()
    }
}