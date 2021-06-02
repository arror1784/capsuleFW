import QtQuick 2.10
import QtQuick.Controls 2.5

DefaultPopup{
    id: popup

    hasBTN: true
    addtionalOffset: -20

    body: Rectangle{

        width: optionText.width + valueText.width + 15
        height: optionText.height

        Column{
            id: optionText
            Text {
                text: qsTr("Version")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("Serial")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("WIFI")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
            Text {
                text: qsTr("IP")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                color: "#474747"
            }
        }
        Column{
            id: valueText
            anchors.left: optionText.right
            anchors.leftMargin: 15
            Text {
                id: verText

                text: qsTr("lower.stl")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 200
                elide: Text.ElideRight
            }
            Text {
                id: modelNoText
                text: qsTr("15min")
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 230
                elide: Text.ElideRight
            }
            Text {
                id: wifiText
                text: ""
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 230
                elide: Text.ElideRight
            }
            Text {
                id: ipText
                text: ""
                font.family: openSansSemibold.name
                font.pixelSize: 23
                font.bold: true
                color: "#474747"

                width: 230
                elide: Text.ElideRight
            }
        }
    }
    AcceptBTN{
        id: closeButton

        width: 185
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        text: qsTr("close")

        onClicked: {
            close()
        }
    }
    onOpened: {
        nc.updateIpAddressList()
        var ipList = nc.getIpAddressList()
        var ip = ""
        if(ipList.length === 0){
            setIPAddress(qsTr("NONE"))
        }else{
            for (var i = 0; i < ipList.length; i++){
                ip += ipList[i] + ":5000\n"
            }
            setIPAddress(ip)
        }
    }

    Connections{
        id: networkConnection
        target: nc
    }
    function setText(version,modelNo){
        verText.text = version
        modelNoText.text = modelNo
    }
    function setWifiConnectd(b){
        if(b){
            wifiText.text = qsTr("Connected")
        }else{
            wifiText.text = qsTr("Disconnected")
        }
    }
    function setIPAddress(address){
        ipText.text = address
    }
}
