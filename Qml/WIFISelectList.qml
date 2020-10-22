import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {
    width: 480
    height: 320

    property string ssidName
    property string currentssidName
    property int currentIndex: -1

    property var networkList

    FontLoader{
        id: openSansSemibold
        source: "qrc:/fonts/OpenSans-SemiBold.ttf"
    }
    FontLoader{
        id: openSansRegular
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }

    ListModel{
        id: wifiModel
    }

    Text {
        id: selectText
        text: qsTr("Select a WIFI ssid")

        font.pixelSize: 23
        font.family: openSansSemibold.name
        font.bold: true
        font.letterSpacing: 2

        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Rectangle{
        id: wifiSelect
        width: 450
        height: 218

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: selectText.bottom
        anchors.topMargin: 5

        radius: 8
        color: "#ffffff"
        ListView{
            id: wifiSelectList
            width: 432
            height: 200
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10

            spacing: 2
            focus: true
            clip: true

            highlightFollowsCurrentItem: true
            highlightMoveDuration: 0
            highlight: Rectangle { color: "#B6CDDC"; height: 22; radius: 5;}

            model: wifiModel
            delegate: WIFIListDelegate{
                onWifiClicked: {
                    wifiSelectList.currentIndex = index
                    currentIndex = index
                    wifiSelectList.update()
                }
            }
        }
    }
    Rectangle{
        id: backButton
        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        color: "#DCEAF3"

        radius: 8

        Text {
            text: qsTr("Back")
            color: "#666666"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                stackView.pop(StackView.Immediate)
            }
        }
    }
    Rectangle{
        id: selectButton

        width: 215
        height: 40

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        color: "#00C6EA"

        radius: 8

        Text {
            text: qsTr("Select")
            color: "#FFFFFF"
            font.family: openSansSemibold.name
            font.pixelSize: 20

            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(wifiSelectList.currentIndex === -1){
                    return
                }
                var data = wifi.getNetwork(wifiSelectList.currentIndex)
                if(data.getConnected()){
                    wifiDisconnectPopup.open(data.ssid,data.bssid)
                }else{
                    wifiConnectPopup.open(data.ssid,data.bssid,data.networkID,data.flags)
                }
            }
        }
    }
    WIFIConnectPopup{
        id:wifiConnectPopup
        onConnectButtonClicked: {
            wifi.networkConnect(ssid,bssid,pwd,id)
            wifi.networkScan()
//            stackView.pop(it,StackView.Immediate)
        }
        onConnectButtonClickedWithoutPSWD: {
            wifi.networkConnect(ssid,bssid,id)
//            wifi.networkScan()
        }
    }
    WIFIDisconnectPopup{
        id: wifiDisconnectPopup
        onDisconnectButtonClicked: {
            wifi.networkDisconnect()
//            wifi.networkScan()
//            stackView.pop(it,StackView.Immediate)
        }
    }
    Connections{
        id: wifiConnection
        target: wifi
        onNetworkListUpdate:{
            updateWIFIList()
        }
        onCurrentStateChange: {
            updateWIFIList()
        }
        onConnectedChange:{
            updateWIFIList()
        }
    }
    WifiInfo{
        id:info
    }

    function updateWIFIList(){
        wifiSelectList.currentIndex = -1
        wifiModel.clear()
        var count = wifi.networkCount()

        for(var i = 0; i < count; i++){
            var data = wifi.getNetwork(i)
            console.log(data)
            inserWIFIList(data.ssid,data.bssid,data.flags,data.connected,data.networkID)
        }
    }
    function inserWIFIList(ssid,bssid,flags,b,networkID){
        wifiModel.append({"ssid":ssid,"bssid":bssid,"flags":flags,"current":b,"networkID":networkID})
    }
    function networkScan(){
        wifi.networkScan()
    }
}
