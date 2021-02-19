import QtQuick 2.12
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true

    property var ipList: []

    body: Text {
        id: ipText
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
    Connections{
        id: networkConnection
        target: nc
    }
    onOpened: {
        nc.updateIpAddressList()
        ipList = nc.getIpAddressList()
        var iptext = ""
        for (var i = 0; i < ipList.length; i++){
            iptext += ipList[i] + ":5000\n"
        }
        ipText.text = iptext
    }
}
