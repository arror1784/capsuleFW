import QtQuick 2.10
import QtQuick.Controls 2.5

Rectangle {

    id: popupBack

    width: 480
    height: 320

    color: "#BDBDBD"
    opacity: 0.7

    visible: false

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

        Rectangle{
            width: optionText.width + valueText.width + 15
            height: optionText.height
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -40
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
        Rectangle{
            id: closeButton

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
        popup.open()
    }
    function close(){
        popup.close()
    }
}
