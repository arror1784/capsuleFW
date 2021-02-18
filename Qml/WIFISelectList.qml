import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

Item {
    width: 480
    height: 320

    property string ssidName
    property string currentssidName
    property int currentIndex: -1
    property bool scanFail: false

    property var networkList

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
        Rectangle{
            id: up

            width: 50
            height: 70

            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8

            Image {
                id: upImage
                anchors.centerIn: parent

                scale: 0.7
                source: "qrc:/image/arrow-up.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    wifiSelectList.flick(0,500)
                }
            }
        }
        Rectangle{
            id: down

            width: 50
            height: 70

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            color: "#B6CDDC"

            radius: 8
            Image {
                id: downImage

                scale: 0.7
                anchors.centerIn: parent
                source: "qrc:/image/arrow-down.png"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    wifiSelectList.flick(0,-500)
                }
            }
        }
    }
    BackBTN{
        id: backButton

        onBackClicked: {
            stackView.pop(StackView.Immediate)
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
                var data = wifiModel.get(wifiSelectList.currentIndex)
                if(data.current){
                    wifiDisconnectPopup.open(data.ssid,data.bssid)
                }else{
                    wifiConnectPopup.open(data.ssid,data.bssid,data.networkID,data.flags)
                }
            }
        }
    }
    WIFITryConnect{
        id: wifiTryConnect
    }

    WIFIConnectPopup{
        id:wifiConnectPopup
        onConnectButtonClicked: {
            wifi.networkConnect(ssid,bssid,pwd,id)
            wifi.networkScan()
        }
        onConnectButtonClickedWithoutPSWD: {
            wifi.networkConnect(ssid,bssid,"",id)
            wifi.networkScan()
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
    WIFINotice{
        id: wifiNotice
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
            if(connected){
                wifiTryConnect.close()
                wifiNotice.setText("WiFi가 연결되었습니다.")
            }else{
                wifiNotice.setText("WiFi 연결이 해제되었습니다.")
            }
            wifiNotice.open()
        }
        onWifiScanFail:{
            if(!scanFail){
                scanFail = true;
                if(value === -52){
                    wifiTryConnect.close()
                    wifiNotice.setText("지원하지 않는 공유기입니다.\n재부팅이 필요합니다.")
                    wifiNotice.open()
                }else{
                    wifiTryConnect.close()
                    wifiNotice.setText("문제가 발생하였습니다." + value)
                    wifiNotice.open()
                }
            }
        }
        onWifiAssocFailed:{
            if(value === 0){
                wifiTryConnect.close()
                wifiNotice.setText("인증에 실패하였습니다.")
                wifiNotice.open()
            }else if(value === 1){
                wifiTryConnect.close()
                wifiNotice.setText("비밀번호 길이가 너무 짧습니다.")
                wifiNotice.open()
            }else if(value === 2){
                wifiTryConnect.close()
                wifiNotice.setText("비밀번호 길이가 너무 깁니다.")
                wifiNotice.open()
            }
        }
        onWifiTryAssociate:{
            wifiTryConnect.open()
        }
    }

    function updateWIFIList(){
        wifiSelectList.currentIndex = -1
        wifiModel.clear()
        var wifiList = wifi.getWifiList()

        for(var i = 0; i < wifiList.length; i++){
            var data = wifiList[i]
            inserWIFIList(data.ssid,data.bssid,data.flags,data.connected,data.networkID)
        }
    }
    function inserWIFIList(ssid,bssid,flags,b,networkID){
        if(b){
            wifiModel.insert(0,{"ssid":ssid,"bssid":bssid,"flags":flags,"current":b,"networkID":networkID})
        }else{
            wifiModel.append({"ssid":ssid,"bssid":bssid,"flags":flags,"current":b,"networkID":networkID})
        }
    }

    function networkScan(){
        wifi.networkScan()
    }
    Component.onCompleted: {
        wifi.networkScan()
    }
}
