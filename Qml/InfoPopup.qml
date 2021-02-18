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
    acceptBTN: AcceptBTN{
        id: closeButton

        isPopup: true

        text: qsTr("close")

        onAcceptClicked: {
            close()
        }
    }
    backBTN: BackBTN{
        id: backButton

        isPopup: true

        onBackClicked: {
            back()
            close()
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
            wifiText.text = "Connected"
        }else{
            wifiText.text = "Disconnected"
        }
    }
    function setIPAddress(address){
        ipText.text = address
    }

    function open(){
        nc.updateIpAddressList()
        var ipList = nc.getIpAddressList()
        var ip = ""
        if(ipList.length === 0){
            setIPAddress("NONE")
        }else{
            for (var i = 0; i < ipList.length; i++){
                ip += ipList[i] + ":5000\n"
            }
            setIPAddress(ip)
        }
        popup.popupOpen()
    }
    function close(){
        popup.popupClose()
    }
}
