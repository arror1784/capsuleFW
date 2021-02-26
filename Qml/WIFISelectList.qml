import QtQuick 2.0
import QtQuick.Controls 2.5
import App 1.0

DefaultListView{
    id: wifiSelectList

    property string ssidName
    property string currentssidName
    property int currentIndex: -1
    property bool scanFail: false

    property var networkList

    ListModel{
        id: wifiModel
    }
    title: qsTr("Select a WIFI ssid")
    model: wifiModel
    delegate: WIFIListDelegate{
        onWifiClicked: {
            wifiSelectList.selectList.currentIndex = index
            currentIndex = index
            wifiSelectList.selectList.update()
        }
    }

    BackBTN{
        id: backButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 15

        onClicked: {
            stackView.pop(StackView.Immediate)
        }
    }
    AcceptBTN{
        id: selectButton

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 15

        text: qsTr("Select")

        onClicked: {
            if(wifiSelectList.selectList.currentIndex === -1){
                return
            }
            var data = wifiModel.get(wifiSelectList.selectList.currentIndex)
            if(data.current){
                wifiDisconnectPopup.openPopup(data.ssid,data.bssid)
            }else{
                wifiConnectPopup.openPopup(data.ssid,data.bssid,data.networkID,data.flags,data.saved)
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
        onConnectButtonClickedWithID: {
            wifi.networkConnect(id)
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
        wifiSelectList.selectList.currentIndex = -1
        wifiModel.clear()
        var wifiList = wifi.getWifiList()

        for(var i = 0; i < wifiList.length; i++){
            var data = wifiList[i]
            inserWIFIList(data.ssid,data.bssid,data.flags,data.connected,data.networkID,data.saved)
        }
    }
    function inserWIFIList(ssid,bssid,flags,b,networkID,saved){
        if(b){
            wifiModel.insert(0,{"ssid":ssid,"bssid":bssid,"flags":flags,"current":b,"networkID":networkID,"saved":saved})
        }else{
            wifiModel.append({"ssid":ssid,"bssid":bssid,"flags":flags,"current":b,"networkID":networkID,"saved":saved})
        }
    }

    function networkScan(){
        wifi.networkScan()
    }
    Component.onCompleted: {
        wifi.networkScan()
    }
}
